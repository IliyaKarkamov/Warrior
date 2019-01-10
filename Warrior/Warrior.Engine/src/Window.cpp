#include "Engine/Window.h"

#include "Engine/Logging/Logging.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "Engine/Input/enums/MouseInput.h"

namespace WarriorEngine
{
namespace detail
{
struct WindowDeleter
{
    void operator()(GLFWwindow* pWindow) const { glfwDestroyWindow(pWindow); }
};

struct WindowImpl
{
    std::unique_ptr<GLFWwindow, WindowDeleter> pWindow_ = nullptr;

    int width_ = 0;
    int height_ = 0;

    float aspectRatio_ = 0.f;
    bool isVSynced_ = false;

    Input::InputManager* pInputManager_ = nullptr;

    void registerKeyboardInput() const;
    void registerMouseInput() const;
};

void WindowImpl::registerKeyboardInput() const
{
    glfwSetKeyCallback(pWindow_.get(), [](GLFWwindow* window, const int key, const int scancode,
                                          const int action, int mods) {
        auto* pImpl = static_cast<detail::WindowImpl*>(glfwGetWindowUserPointer(window));

        if (!pImpl->pInputManager_)
            return;

        auto pressed = false;

        if (action == GLFW_PRESS)
            pressed = true;
        else if (action == GLFW_RELEASE)
            pressed = false;
        else
            return;

        pImpl->pInputManager_->processButton(Input::RawInput(Input::RawInputType::Keyboard, key), pressed);
    });
}

void WindowImpl::registerMouseInput() const
{
    glfwSetMouseButtonCallback(pWindow_.get(), [](GLFWwindow* window, int button, int action, int mods) {
        auto* pImpl = static_cast<detail::WindowImpl*>(glfwGetWindowUserPointer(window));

        if (!pImpl->pInputManager_)
            return;

        auto pressed = false;

        if (action == GLFW_PRESS)
            pressed = true;
        else if (action == GLFW_RELEASE)
            pressed = false;
        else
            return;

        pImpl->pInputManager_->processButton(Input::RawInput(Input::RawInputType::MouseButton, button),
                                             pressed);
    });

    glfwSetCursorPosCallback(pWindow_.get(), [](GLFWwindow* window, const double xpos, const double ypos) {
        auto* pImpl = static_cast<detail::WindowImpl*>(glfwGetWindowUserPointer(window));

        if (!pImpl->pInputManager_)
            return;

        pImpl->pInputManager_->processMove(
            Input::RawInput(Input::RawInputType::MouseMove,
                            static_cast<int>(Input::MouseInputAxis::MouseAxisX)),
            xpos);

        pImpl->pInputManager_->processMove(
            Input::RawInput(Input::RawInputType::MouseMove,
                            static_cast<int>(Input::MouseInputAxis::MouseAxisY)),
            ypos);
    });

    glfwSetScrollCallback(pWindow_.get(), [](GLFWwindow* window, const double xoffset, const double yoffset) {
        auto* pImpl = static_cast<detail::WindowImpl*>(glfwGetWindowUserPointer(window));

        if (!pImpl->pInputManager_)
            return;

        pImpl->pInputManager_->processScroll(
            Input::RawInput(Input::RawInputType::MouseScroll, static_cast<int>(Input::MouseScroll::X)),
            xoffset);

        pImpl->pInputManager_->processScroll(
            Input::RawInput(Input::RawInputType::MouseScroll, static_cast<int>(Input::MouseScroll::Y)),
            yoffset);
    });
}
}  // namespace detail

void Window::hide() const { glfwHideWindow(pImpl_->pWindow_.get()); }

void Window::show() const { glfwShowWindow(pImpl_->pWindow_.get()); }

void Window::focus() const { glfwFocusWindow(pImpl_->pWindow_.get()); }

int Window::getWidth() const noexcept { return pImpl_->width_; }

int Window::getHeight() const noexcept { return pImpl_->height_; }

float Window::getAspectRatio() const noexcept { return pImpl_->aspectRatio_; }

void Window::fullscreen() const
{
    const auto monitor = glfwGetPrimaryMonitor();
    const auto mode = glfwGetVideoMode(monitor);

    glfwSetWindowMonitor(pImpl_->pWindow_.get(), monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    glfwGetWindowSize(pImpl_->pWindow_.get(), &pImpl_->width_, &pImpl_->height_);
}

Window::Window(const int width, const int height, const std::string& title)
    : pImpl_(std::make_shared<detail::WindowImpl>())
{
    if (!glfwInit())
        throw std::runtime_error("Warrior.Engine.Display error: unable to initialize glfw.");

    const auto monitor = glfwGetPrimaryMonitor();
    const auto mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    pImpl_->pWindow_.reset(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr));

    if (!pImpl_->pWindow_)
    {
        glfwTerminate();
        WE_ENGINE_ERROR("Warrior.Engine.Display error: unable to create window.");
        return;
    }

    glfwSetWindowUserPointer(pImpl_->pWindow_.get(), pImpl_.get());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwMakeContextCurrent(pImpl_->pWindow_.get());

    glfwSetWindowSizeCallback(
        pImpl_->pWindow_.get(), [](GLFWwindow* pWindow, const int width, const int height) {
            auto* pImpl = static_cast<detail::WindowImpl*>(glfwGetWindowUserPointer(pWindow));

            pImpl->width_ = width;
            pImpl->height_ = height;

            if (pImpl->width_ > 0 && pImpl->height_ > 0)
                pImpl->aspectRatio_ = pImpl->width_ / static_cast<float>(pImpl->height_);
        });

    pImpl_->registerKeyboardInput();
    pImpl_->registerMouseInput();

    glfwGetWindowSize(pImpl_->pWindow_.get(), &pImpl_->width_, &pImpl_->height_);

    if (glewInit() != GLEW_OK)
        WE_ENGINE_ERROR("Warrior.Engine.Display error: glew initialization failed.");
}

Window::~Window() { glfwTerminate(); }

void Window::setInputManager(Input::InputManager* pInputManager) const
{
    pImpl_->pInputManager_ = pInputManager;
}

bool Window::isAlive() const { return !glfwWindowShouldClose(pImpl_->pWindow_.get()); }

void Window::vSync(const bool enable) const
{
    if (enable)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    pImpl_->isVSynced_ = enable;
}

bool Window::isVSync() const
{
    return pImpl_->isVSynced_; 
}

void Window::pollEvents() const { glfwPollEvents(); }

void Window::draw() const { glfwSwapBuffers(pImpl_->pWindow_.get()); }

}  // namespace WarriorEngine
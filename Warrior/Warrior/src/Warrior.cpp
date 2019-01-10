#include <Engine/WarriorEngine.h>

#include <Engine/Graphics/Camera.h>
#include "Terrain/Terrain.h"
#include "Terrain/TerrainLoader.h"
#include "Skydom/Skydom.h"
#include "GameObject.h"
#include "GameObjectsLoader.h"
#include <filesystem>

using namespace WarriorEngine;
namespace GL = Graphics::OpenGL;

class WarriorGame : public Application
{
    Resources::Resource<Graphics::Camera> camera_ = nullptr;
    Resources::Resource<Input::InputListener> listener_ = nullptr;

    std::unique_ptr<Graphics::Light> light_ = nullptr;
    std::unique_ptr<GameObject> sun_ = nullptr;

    std::unique_ptr<Warrior::Terrain::Terrain> terrain_ = nullptr;
    std::unique_ptr<Warrior::Skydom::Skydom> skydom_ = nullptr;

    std::vector<GameObject> gameObjects_;

    std::unique_ptr<GameObject> ba2_ = nullptr;

    void onInputDispatch(const Input::MappedInput& mappedData,
                         const Input::CursorPosition& cursorPosition) const;

public:
    void initialize() override;
    void update() override;
    void draw() override;
};

void WarriorGame::onInputDispatch(const Input::MappedInput& mappedData,
                                  const Input::CursorPosition& cursorPosition) const
{
    for (auto&& action : mappedData.actions)
        if (action == 0)
        {
            static auto wireframeMode = false;
            GL::Renderer::wireframe(wireframeMode);

            wireframeMode = !wireframeMode;
        }

    constexpr auto speed = 2.3f;

    for (auto&& state : mappedData.states)
    {
        if (state == 0)
            camera_->move(Graphics::MoveDirection::Left, speed);
        else if (state == 1)
            camera_->move(Graphics::MoveDirection::Right, speed);
        else if (state == 2)
            camera_->move(Graphics::MoveDirection::Forward, speed);
        else if (state == 3)
            camera_->move(Graphics::MoveDirection::Backward, speed);
    }

    if (const auto it = mappedData.states.find(4); it == mappedData.states.end())
        return;

    auto xOffset = 0.f, yOffset = 0.f;

    for (auto&& [range, value] : mappedData.ranges)
    {
        const auto finalValue = value * 0.5;

        if (range == 0)
            xOffset = finalValue;
        else if (range == 1)
            yOffset = finalValue;
        else if (range == 2)
        {
            camera_->updateZoom(finalValue);
            continue;
        }

        camera_->updateYaw(xOffset);
        camera_->updatePitch(yOffset);
    }

    auto update = false;

    if (cursorPosition.x <= 0)
    {
        xOffset = -speed;
        update = true;
    }
    else if (cursorPosition.x >= getWindow().getWidth() - 1)
    {
        xOffset = speed;
        update = true;
    }

    if (cursorPosition.y <= 0)
    {
        yOffset = -speed;
        update = true;
    }
    else if (cursorPosition.y >= getWindow().getHeight() - 1)
    {
        yOffset = speed;
        update = true;
    }

    if (update)
    {
        camera_->updateYaw(xOffset);
        camera_->updatePitch(yOffset);
    }
}

void WarriorGame::initialize()
{
    WE_INFO("Application initialization begin");

    auto& window = getWindow();
    auto& resourceManager = getResourceManager();

    window.focus();
    window.fullscreen();
    window.vSync(true);

    resourceManager.setResourcesPath(R"(res)");

    WE_INFO("Application initialization end");
    WE_INFO("%s", std::filesystem::current_path().string().c_str());
    WE_TRACE("%dx%d", window.getWidth(), window.getHeight());

    GL::Renderer::viewport(0, 0, window.getWidth(), window.getHeight());
    GL::Renderer::enable(GL::Capability::DepthTest);
    GL::Renderer::enable(GL::Capability::CullFace);
    GL::Renderer::cullFace(GL::CullFaceMode::Back);

    GL::Renderer::enable(GL::Capability::Blend);
    GL::Renderer::blendFunc(GL::BlendingFactor::SrcAlpha, GL::BlendingFactor::OneMinusSrcAlpha);

    camera_ = resourceManager.getCamera(R"(camera/camera.json)");
    listener_ = resourceManager.getInputListener(R"(camera/input.json)");

    listener_->setDispatchCallback(
        [this](const Input::MappedInput& mappedData, const Input::CursorPosition& cursorPosition) {
            onInputDispatch(mappedData, cursorPosition);
        });

    getInputManager().addListener(10, listener_.get());

    {
        Warrior::Terrain::TerrainLoader loader(resourceManager);
        terrain_ = loader.fromFile(R"(terrain/terrain.json)");
    }

    light_ = std::make_unique<Graphics::Light>(glm::vec3(400, 300, 250), glm::vec3(1.f, 1.f, 1.f));

    {
        auto modelMatrix = translate(glm::mat4(1.f), glm::vec3(400, 300, 250));
        modelMatrix = scale(modelMatrix, glm::vec3(16.f, 16.f, 16.f));

        sun_ = std::make_unique<GameObject>(resourceManager.getProgram(R"(models/sun/shaders/sun)"),
                                            resourceManager.getModel(R"(models/sun/sun.obj)"), modelMatrix);
    }

    {
        GameObjectsLoader loader(resourceManager);
        gameObjects_ = loader.fromFile(R"(game_objects.json)");
    }

    skydom_ = std::make_unique<Warrior::Skydom::Skydom>(resourceManager.getProgram("skydom/shaders/skydom"),
                                                        resourceManager.getCubeMap("skydom/skydom.json"));
    {
        auto modelMatrix = translate(glm::mat4(1.f), glm::vec3(10, 50, -10));
        modelMatrix = scale(modelMatrix, glm::vec3(2.f, 2.f, 2.f));
        ba2_ = std::make_unique<GameObject>(resourceManager.getProgram(R"(shaders/static_entity)"),
                                            resourceManager.getModel(R"(models/ba2/ba2.obj)"), modelMatrix);
    }
}

void WarriorGame::update()
{
    static auto xSpeed = 0.005f;

    auto currentPos = light_->getPosition();

    if (currentPos.x <= -500.f)
        currentPos.x = 1300.f;
    else if (currentPos.x >= 1300)
        currentPos.x = -500.f;

    light_->setPosition({currentPos.x + xSpeed, currentPos.y, currentPos.z});

    {
        auto modelMatrix = translate(glm::mat4(1.f), light_->getPosition());
        modelMatrix = scale(modelMatrix, glm::vec3(16.f, 16.f, 16.f));

        sun_->setModelMatrix(modelMatrix);
    }

    terrain_->loadLight(*light_);

    {
        static auto koko = 0.002f;
        auto modelMatrix = translate(glm::mat4(1.f), glm::vec3(10, 50, -10));
        modelMatrix = rotate(modelMatrix, glm::radians(koko), glm::vec3(1.f, 1.f, 1.f));
        modelMatrix = scale(modelMatrix, glm::vec3(2.f, 2.f, 2.f));

        ba2_->setModelMatrix(modelMatrix);

        koko += 0.002f;
    }
}

void WarriorGame::draw()
{
    WE_INFO("FPS: %f", getFps());

    GL::Renderer::clearColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.f));
    GL::Renderer::clear(Graphics::OpenGL::BufferType::Color | Graphics::OpenGL::BufferType::Depth);

    const auto projection = glm::perspective(glm::radians(camera_->getZoom()), 16.f / 9.f, 0.1f, 1200.f);
    const auto view = camera_->getViewMatrix();

    terrain_->draw(view, projection, camera_->getPosition());

    for (auto&& object : gameObjects_)
        object.draw(view, projection, *light_, camera_->getPosition());

    GL::Renderer::depthFunc(Graphics::OpenGL::DepthFunc::LEqual);
    skydom_->draw(projection, view);
    GL::Renderer::depthFunc(Graphics::OpenGL::DepthFunc::Less);

    sun_->draw(view, projection, *light_, camera_->getPosition());
    ba2_->draw(view, projection, *light_, camera_->getPosition());
}

Application* WarriorEngine::createApplication() { return new WarriorGame(); }

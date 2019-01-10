#include "Engine/Resources/Loaders/InputListenerLoader.h"
#include "Engine/Logging/Logging.h"
#include <nlohmann/json.hpp>
#include <fstream>

namespace WarriorEngine::Resources::Loaders
{
std::unique_ptr<Input::InputListener> InputListenerLoader::fromFile(const std::string& file) const
{
    using nlohmann::json;

    std::ifstream ifs(file);

    if (!ifs.is_open())
    {
        WE_ENGINE_ERROR("Warior.Engine.Input.InputListener error: Error while trying to read input file: %s",
                        file.c_str());
        return nullptr;
    }

    json j;
    ifs >> j;

    std::map<Input::RawInput, int> actionsMapping;
    std::map<Input::RawInput, int> statesMapping;
    std::map<Input::RawInput, Input::RangeInput> rangesMapping;

    if (auto& actions = j["actions"]; !actions.is_null())
    {
        for (auto it = actions.begin(); it != actions.end(); ++it)
        {
            auto& action = it.value();

            Input::RawInputType rawInputType;
            int rawInputValue, actionValue;

            // input type
            {
                auto& inputType = action["inputType"];

                if (inputType.is_null() || !inputType.is_number_integer())
                    continue;

                rawInputType = static_cast<Input::RawInputType>(inputType.get<int>());
            }

            // input value
            {
                auto& inputValue = action["inputValue"];

                if (inputValue.is_null() || !inputValue.is_number_integer())
                    continue;

                rawInputValue = inputValue.get<int>();
            }

            // action
            {
                auto& actionVal = action["action"];

                if (actionVal.is_null() || !actionVal.is_number_integer())
                    continue;

                actionValue = actionVal.get<int>();
            }

            const Input::RawInput rawInput(rawInputType, rawInputValue);
            actionsMapping[rawInput] = actionValue;
        }
    }

    if (auto& states = j["states"]; !states.is_null())
    {
        for (auto it = states.begin(); it != states.end(); ++it)
        {
            auto& state = it.value();

            Input::RawInputType rawInputType;
            int rawInputValue, stateValue;

            // input type
            {
                auto& inputType = state["inputType"];

                if (inputType.is_null() || !inputType.is_number_integer())
                    continue;

                rawInputType = static_cast<Input::RawInputType>(inputType.get<int>());
            }

            // input value
            {
                auto& inputValue = state["inputValue"];

                if (inputValue.is_null() || !inputValue.is_number_integer())
                    continue;

                rawInputValue = inputValue.get<int>();
            }

            // state
            {
                auto& actionVal = state["state"];

                if (actionVal.is_null() || !actionVal.is_number_integer())
                    continue;

                stateValue = actionVal.get<int>();
            }

            const Input::RawInput rawInput(rawInputType, rawInputValue);
            statesMapping[rawInput] = stateValue;
        }
    }

    if (auto& ranges = j["ranges"]; !ranges.is_null())
    {
        for (auto it = ranges.begin(); it != ranges.end(); ++it)
        {
            auto& range = it.value();

            Input::RawInputType rawInputType;
            int rawInputValue, rangeValue;
            int minimumInput, maximumInput, minimumOutput, maximumOutput;

            // input type
            {
                auto& inputType = range["inputType"];

                if (inputType.is_null() || !inputType.is_number_integer())
                    continue;

                rawInputType = static_cast<Input::RawInputType>(inputType.get<int>());
            }

            // input value
            {
                auto& inputValue = range["inputValue"];

                if (inputValue.is_null() || !inputValue.is_number_integer())
                    continue;

                rawInputValue = inputValue.get<int>();
            }

            // range
            {
                auto& actionVal = range["range"];

                if (actionVal.is_null() || !actionVal.is_number_integer())
                    continue;

                rangeValue = actionVal.get<int>();
            }

            // minimumInput
            {
                auto& minInput = range["minimumInput"];

                if (minInput.is_null() || !minInput.is_number_integer())
                    continue;

                minimumInput = minInput.get<int>();
            }

            // maximumInput
            {
                auto& maxInput = range["maximumInput"];

                if (maxInput.is_null() || !maxInput.is_number_integer())
                    continue;

                maximumInput = maxInput.get<int>();
            }

            // minimumOutput
            {
                auto& minOutput = range["minimumOutput"];

                if (minOutput.is_null() || !minOutput.is_number_integer())
                    continue;

                minimumOutput = minOutput.get<int>();
            }

            // maximumOutput
            {
                auto& maxOutput = range["maximumOutput"];

                if (maxOutput.is_null() || !maxOutput.is_number_integer())
                    continue;

                maximumOutput = maxOutput.get<int>();
            }

            const Input::RawInput rawInput(rawInputType, rawInputValue);

            auto normalizer = std::make_unique<Input::ValueNormalizer>(minimumInput, maximumInput,
                                                                       minimumOutput, maximumOutput);

            Input::RangeInput rangeInput;
            rangeInput.range = rangeValue;
            rangeInput.pNormalizer = std::move(normalizer);

            rangesMapping[rawInput] = std::move(rangeInput);
        }
    }

    return std::make_unique<Input::InputListener>(std::move(actionsMapping), std::move(statesMapping),
                                                  std::move(rangesMapping));
}
}  // namespace WarriorEngine::Resources::Loaders

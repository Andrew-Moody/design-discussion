#ifndef NOSINGLETON
#define NOSINGLETON

#include <iostream>
#include <string>
#include <limits>
#include <cassert>
#include <map>

namespace nosingleton
{
    // States only need to know the enum value of the state they wish to
    // transition to rather than the class name of the state
    // This way states need only include a header containing the enum
    // instead of all the headers of states they are interested in
    enum class StateName
    {
        StartState,
        MainMenuState,
        CollectNameState,
        CollectAddressState,
        CollectAgeState,
        CollectHeightState,
        EditNameState,
        EditAddressState,
        EditAgeState,
        EditHeightState,
        ConfirmInfoState,
        EditOptionsState,
        FinishedState
    };

    struct Patient
    {
        // Information learned by the bot
        std::string name;
        std::string address;
        int age;
        int height;
    };

    class ChatBot;

    class State
    {
    public:

        // Request handlers
        virtual void prompt_user(ChatBot* bot);
        virtual void process_input(ChatBot* bot);

        // State is a friend of Chatbot (the context), but derived states
        // are not. Derived states must use this function instead
        void change_state(ChatBot* bot, StateName name);

        // Helper functions that give derived states access to the context
        void set_patient_name(ChatBot* bot, std::string name);
        void set_patient_address(ChatBot* bot, std::string address);
        void set_patient_age(ChatBot* bot, int age);
        void set_patient_height(ChatBot* bot, int height);

        virtual ~State() = 0;
    };

    State::~State() = default;

    class StateSet;

    class ChatBot
    {
    public:

        ChatBot(StateSet* state_set);

        bool running() const;

        // Forward requests to the current state
        void prompt_user() { current_state_->prompt_user(this); };
        void process_input() { current_state_->process_input(this); };

        const Patient& get_patient_info() const { return patient_; }

    private:

        // This allows only states to have access to state specific functions
        // of the chatbot protecting chatbot from having it's state
        // be directly altered from the outside
        friend State;

        void change_state(StateName name);

        State* current_state_{};

        StateSet* state_set_{};

        Patient patient_;
    };

    // States

    class StartState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class MainMenuState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class CollectNameState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class CollectAddressState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class CollectAgeState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class CollectHeightState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };


    class EditNameState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class EditAddressState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class EditAgeState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class EditHeightState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class ConfirmInfoState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class EditOptionsState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class FinishedState : public State
    {
    public:

        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };


    // Has to be defined after all of the states to be able to instantiate them
    class StateSet
    {
    public:

        StateSet()
        {
            states_[StateName::StartState] = &start_state_;
            states_[StateName::MainMenuState] = &main_menu_state_;
            states_[StateName::CollectNameState] = &collect_name_state_;
            states_[StateName::CollectAddressState] = &collect_address_state_;
            states_[StateName::CollectAgeState] = &collect_age_state_;
            states_[StateName::CollectHeightState] = &collect_height_state_;
            states_[StateName::EditNameState] = &edit_name_state_;
            states_[StateName::EditAddressState] = &edit_address_state_;
            states_[StateName::EditAgeState] = &edit_age_state_;
            states_[StateName::EditHeightState] = &edit_height_state_;
            states_[StateName::ConfirmInfoState] = &confirm_info_state_;
            states_[StateName::EditOptionsState] = &edit_options_state_;
            states_[StateName::FinishedState] = &finished_state_;

            StartState start_state_{};
            MainMenuState main_menu_state_{};
            CollectNameState collect_name_state_{};
            CollectAddressState collect_address_state_{};
            CollectAgeState collect_age_state_{};
            CollectHeightState collect_height_state_{};
            EditNameState edit_name_state_{};
            EditAddressState edit_address_state_{};
            EditAgeState edit_age_state_{};
            EditHeightState edit_height_state_{};
            ConfirmInfoState confirm_info_state_{};
            EditOptionsState edit_options_state_{};
            FinishedState finished_state_{};
        }

        State* get_state(StateName name)
        {
            auto iter = states_.find(name);

            // Here I want there to never be a state that can't be found
            // A more sophisticated system might use a default state instead
            assert(iter != states_.end());

            State* state = iter->second;

            // Really don't want to users of the state set to have to deal
            // with null pointers
            assert(state);

            return state;
        }

    private:

        std::map<StateName, State*> states_;

        StartState start_state_{};
        MainMenuState main_menu_state_{};
        CollectNameState collect_name_state_{};
        CollectAddressState collect_address_state_{};
        CollectAgeState collect_age_state_{};
        CollectHeightState collect_height_state_{};
        EditNameState edit_name_state_{};
        EditAddressState edit_address_state_{};
        EditAgeState edit_age_state_{};
        EditHeightState edit_height_state_{};
        ConfirmInfoState confirm_info_state_{};
        EditOptionsState edit_options_state_{};
        FinishedState finished_state_{};
    };



    // Utility function to "Clear" the console window
    void clear_screen();

    // Start State
    void StartState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Welcome\n\n\n\n\nPress enter to start" << std::endl;
    }

    void StartState::process_input(ChatBot* bot)
    {
        std::string line;
        getline(std::cin, line);

        std::cout << "Contents: (" << line << ')' << std::endl;

        change_state(bot, StateName::MainMenuState);
    }


    // MainMenu State
    void MainMenuState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Main Menu\n\n\n\n\n";
        std::cout << "1. Add Patient\n2. Exit\n\n\n";
        std::cout << "Type a number according to your selection and press enter\n" << std::endl;
    }

    void MainMenuState::process_input(ChatBot* bot)
    {
        int in;
        std::cin >> in;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (in)
        {
        case 1:
        {
            change_state(bot, StateName::CollectNameState);
            break;
        }
        case 2:
        {
            change_state(bot, StateName::FinishedState);
            break;
        }
        default:
        {
            break;
        }
        }
    }


    // CollectName State
    void CollectNameState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Add Patient Name\n\n\n\n\n\n";
        std::cout << "Type your name and press enter\n" << std::endl;
    }

    void CollectNameState::process_input(ChatBot* bot)
    {
        std::string name;
        getline(std::cin, name);
        set_patient_name(bot, name);
        change_state(bot, StateName::CollectAddressState);
    }


    // CollectAddress State
    void CollectAddressState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Add Patient Address\n\n\n\n\n\n";
        std::cout << "Type your address and press enter\n" << std::endl;
    }

    void CollectAddressState::process_input(ChatBot* bot)
    {
        std::string address;
        getline(std::cin, address);
        set_patient_address(bot, address);
        change_state(bot, StateName::CollectAgeState);
    }


    // CollectAge State
    void CollectAgeState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Add Patient Age\n\n\n\n\n\n";
        std::cout << "Type your age and press enter\n" << std::endl;
    }

    void CollectAgeState::process_input(ChatBot* bot)
    {
        int age{};
        std::cin >> age;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        set_patient_age(bot, age);
        change_state(bot, StateName::CollectHeightState);
    }


    // CollectHeight State
    void CollectHeightState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Add Patient Height\n\n\n\n\n\n";
        std::cout << "Type your height and press enter\n" << std::endl;
    }

    void CollectHeightState::process_input(ChatBot* bot)
    {
        int height{};
        std::cin >> height;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        set_patient_height(bot, height);
        change_state(bot, StateName::ConfirmInfoState);
    }


    // EditName State
    void EditNameState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Edit Patient Name\n\n\n\n\n\n";
        std::cout << "Type your name and press enter\n" << std::endl;
    }

    void EditNameState::process_input(ChatBot* bot)
    {
        std::string name;
        getline(std::cin, name);
        set_patient_name(bot, name);
        change_state(bot, StateName::EditOptionsState);
    }


    // EditAddress State
    void EditAddressState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Edit Patient Address\n\n\n\n\n\n";
        std::cout << "Type your address and press enter\n" << std::endl;
    }

    void EditAddressState::process_input(ChatBot* bot)
    {
        std::string address;
        getline(std::cin, address);
        set_patient_address(bot, address);
        change_state(bot, StateName::EditOptionsState);
    }


    // EditAge State
    void EditAgeState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Edit Patient Age\n\n\n\n\n\n";
        std::cout << "Type your age and press enter\n" << std::endl;
    }

    void EditAgeState::process_input(ChatBot* bot)
    {
        int age{};
        std::cin >> age;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        set_patient_age(bot, age);
        change_state(bot, StateName::EditOptionsState);
    }


    // EditHeight State
    void EditHeightState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Edit Patient Height\n\n\n\n\n\n";
        std::cout << "Type your height and press enter\n" << std::endl;
    }

    void EditHeightState::process_input(ChatBot* bot)
    {
        int height{};
        std::cin >> height;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        set_patient_height(bot, height);
        change_state(bot, StateName::EditOptionsState);
    }


    // ConfirmInfo State
    void ConfirmInfoState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        Patient patient{ bot->get_patient_info() };

        std::cout << "Confirm Info is Correct\n\n\n";
        std::cout << "Patient Name: " << patient.name << '\n';
        std::cout << "Patient Address: " << patient.address << '\n';
        std::cout << "Patient Age: " << patient.age << '\n';
        std::cout << "Patient Height: " << patient.height << "\n\n\n";
        std::cout << "1. Edit Patient Info\n2. Save and Return to Menu\n\n\n";
        std::cout << "Type a number according to your selection and press enter\n" << std::endl;
    }

    void ConfirmInfoState::process_input(ChatBot* bot)
    {
        int in;
        std::cin >> in;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (in)
        {
        case 1:
        {
            change_state(bot, StateName::EditOptionsState);
            break;
        }
        case 2:
        {
            change_state(bot, StateName::MainMenuState);
            break;
        }
        default:
        {
            break;
        }
        }
    }


    // EditOptions State
    void EditOptionsState::prompt_user(ChatBot* bot)
    {
        clear_screen();

        std::cout << "Edit Patient Info\n\n\n\n\n";
        std::cout << "1. Edit Name\n2. Edit Address\n3. Edit Age\n4. Edit Height\n5. Save and Continue\n\n\n";
        std::cout << "Type a number according to your selection and press enter\n" << std::endl;
    }

    void EditOptionsState::process_input(ChatBot* bot)
    {
        int in;
        std::cin >> in;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (in)
        {
        case 1:
        {
            change_state(bot, StateName::EditNameState);
            break;
        }
        case 2:
        {
            change_state(bot, StateName::EditAddressState);
            break;
        }
        case 3:
        {
            change_state(bot, StateName::EditAgeState);
            break;
        }
        case 4:
        {
            change_state(bot, StateName::EditHeightState);
            break;
        }
        case 5:
        {
            change_state(bot, StateName::ConfirmInfoState);
            break;
        }
        default:
        {
            break;
        }
        }
    }


    // Finished State
    void FinishedState::prompt_user(ChatBot* bot)
    {

    }

    void FinishedState::process_input(ChatBot* bot)
    {

    }


    void run_nosingleton_demo()
    {
        // Whether this is stack or heap doesn't matter
        // but used stack to prove it was possible
        // It is also possible to have ChatBot own the
        // StateSet if reuse is not required or the states
        // themselves maintain state and cannot be shared
        StateSet state_set{};

        ChatBot bot{ &state_set };

        while (bot.running())
        {
            bot.prompt_user();
            bot.process_input();
        }
    }

    // Patient editing helpers

    void State::change_state(ChatBot* bot, StateName name)
    {
        assert(bot);
        bot->change_state(name);
    }

    void State::set_patient_name(ChatBot* bot, std::string name)
    {
        bot->patient_.name = name;
    }

    void State::set_patient_address(ChatBot* bot, std::string address)
    {
        bot->patient_.address = address;
    }

    void State::set_patient_age(ChatBot* bot, int age)
    {
        bot->patient_.age = age;
    }

    void State::set_patient_height(ChatBot* bot, int height)
    {
        bot->patient_.height = height;
    }

    // ChatBot Implementation
    ChatBot::ChatBot(StateSet* state_set)
        : state_set_(state_set)
    {
        change_state(StateName::StartState);
    }

    void ChatBot::change_state(StateName name)
    {
        current_state_ = state_set_->get_state(name);
        assert(current_state_);
    }

    bool ChatBot::running() const
    {
        // Inefficient but thats not important for this demo
        return current_state_ != state_set_->get_state(StateName::FinishedState);
    }


    // Default handler implementations

    void State::prompt_user(ChatBot* bot)
    {
        std::cout << "Error: State does not implement State::prompt_user" << std::endl;
    }

    void State::process_input(ChatBot* bot)
    {
        std::cout << "Error: State does not implement State::process_input" << std::endl;
    }

    // Helper to "clear the screen"
    void clear_screen()
    {
        for (int i = 0; i < 100; ++i)
        {
            std::cout << "\n";
        }

        std::cout << std::endl;
    }
}

#endif
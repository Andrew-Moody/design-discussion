#ifndef CHATBOT
#define CHATBOT

#include <iostream>
#include <string>

namespace chat
{

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
        void change_state(ChatBot* bot, State* state);

        // Helper functions that give derived states access to the context
        void set_patient_name(ChatBot* bot, std::string name);
        void set_patient_address(ChatBot* bot, std::string address);
        void set_patient_age(ChatBot* bot, int age);
        void set_patient_height(ChatBot* bot, int height);

        virtual ~State() = 0;
    };

    State::~State() = default;

    class ChatBot
    {
    public:

        ChatBot();

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

        void change_state(State* state)
        {
            assert(state);

            current_state_ = state;
        }

        State* current_state_{};

        Patient patient_;
    };

    // States

    class StartState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class MainMenuState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class CollectNameState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class CollectAddressState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class CollectAgeState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class CollectHeightState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };


    class EditNameState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class EditAddressState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class EditAgeState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class EditHeightState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class ConfirmInfoState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class EditOptionsState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
    };

    class FinishedState : public State
    {
    public:

        static State* instance();
        virtual void prompt_user(ChatBot* bot) override;
        virtual void process_input(ChatBot* bot) override;
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

        change_state(bot, MainMenuState::instance());
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
            change_state(bot, CollectNameState::instance());
            break;
        }
        case 2:
        {
            change_state(bot, FinishedState::instance());
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
        change_state(bot, CollectAddressState::instance());
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
        change_state(bot, CollectAgeState::instance());
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
        change_state(bot, CollectHeightState::instance());
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
        change_state(bot, ConfirmInfoState::instance());
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
        change_state(bot, EditOptionsState::instance());
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
        change_state(bot, EditOptionsState::instance());
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
        change_state(bot, EditOptionsState::instance());
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
        change_state(bot, EditOptionsState::instance());
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
            change_state(bot, EditOptionsState::instance());
            break;
        }
        case 2:
        {
            change_state(bot, MainMenuState::instance());
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
            change_state(bot, EditNameState::instance());
            break;
        }
        case 2:
        {
            change_state(bot, EditAddressState::instance());
            break;
        }
        case 3:
        {
            change_state(bot, EditAgeState::instance());
            break;
        }
        case 4:
        {
            change_state(bot, EditHeightState::instance());
            break;
        }
        case 5:
        {
            change_state(bot, ConfirmInfoState::instance());
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


    void run_chat_demo()
    {
        ChatBot bot{};

        while (bot.running())
        {
            bot.prompt_user();
            bot.process_input();
        }
    }

    void State::change_state(ChatBot* bot, State* state)
    {
        assert(bot);
        bot->change_state(state);
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

    ChatBot::ChatBot()
    {
        change_state(StartState::instance());
    }

    bool ChatBot::running() const
    {
        return current_state_ != FinishedState::instance();
    }

    State* StartState::instance()
    {
        static StartState state;
        return &state;
    }

    State* MainMenuState::instance()
    {
        static MainMenuState state;
        return &state;
    }

    State* CollectNameState::instance()
    {
        static CollectNameState state;
        return &state;
    }

    State* CollectAddressState::instance()
    {
        static CollectAddressState state;
        return &state;
    }

    State* CollectAgeState::instance()
    {
        static CollectAgeState state;
        return &state;
    }

    State* CollectHeightState::instance()
    {
        static CollectHeightState state;
        return &state;
    }

    State* EditNameState::instance()
    {
        static EditNameState state;
        return &state;
    }

    State* EditAddressState::instance()
    {
        static EditAddressState state;
        return &state;
    }

    State* EditAgeState::instance()
    {
        static EditAgeState state;
        return &state;
    }

    State* EditHeightState::instance()
    {
        static EditHeightState state;
        return &state;
    }

    State* ConfirmInfoState::instance()
    {
        static ConfirmInfoState state;
        return &state;
    }

    State* EditOptionsState::instance()
    {
        static EditOptionsState state;
        return &state;
    }

    State* FinishedState::instance()
    {
        static FinishedState state;
        return &state;
    }


    void State::prompt_user(ChatBot* bot)
    {
        std::cout << "Error: State does not implement State::prompt_user" << std::endl;
    }

    void State::process_input(ChatBot* bot)
    {
        std::cout << "Error: State does not implement State::process_input" << std::endl;
    }

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
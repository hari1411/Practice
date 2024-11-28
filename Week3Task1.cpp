#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Class representing a menu item
class MenuItem {
public:
    std::string name;
    std::vector<std::shared_ptr<MenuItem>> subMenu;

    MenuItem(const std::string& name) : name(name) {}
    
    void addSubItem(const std::shared_ptr<MenuItem>& item) {
        subMenu.push_back(item);
    }
};

// Class representing the menu system
class MenuSystem {
private:
    std::shared_ptr<MenuItem> root;
    std::shared_ptr<MenuItem> currentMenu;
    std::vector<std::shared_ptr<MenuItem>> menuPath;

    void displayMenu() {
        std::cout << "\n-- " << currentMenu->name << " --\n";
        for (size_t i = 0; i < currentMenu->subMenu.size(); ++i) {
            std::cout << i + 1 << ". " << currentMenu->subMenu[i]->name << "\n";
        }
        std::cout << "0. Back\n";
    }

    void navigateUp() {
        if (!menuPath.empty()) {
            currentMenu = menuPath.back();
            menuPath.pop_back();
        } else {
            std::cout << "Already at the top level.\n";
        }
    }

    void navigateDown(int index) {
        if (index > 0 && index <= static_cast<int>(currentMenu->subMenu.size())) {
            menuPath.push_back(currentMenu);
            currentMenu = currentMenu->subMenu[index - 1];
        } else {
            std::cout << "Invalid selection. Try again.\n";
        }
    }

public:
    MenuSystem(const std::shared_ptr<MenuItem>& rootMenu) : root(rootMenu), currentMenu(rootMenu) {}

    void run() {
        while (true) {
            displayMenu();
            std::cout << "\nEnter your choice: ";
            int choice;
            std::cin >> choice;

            if (choice == 0) {
                navigateUp();
            } else {
                navigateDown(choice);
            }

            if (currentMenu == root && menuPath.empty()) {
                std::cout << "Exited the menu system.\n";
                break;
            }
        }
    }
};

int main() {
    // Building the menu structure
    auto mainMenu = std::make_shared<MenuItem>("Main Menu");
    auto settings = std::make_shared<MenuItem>("Settings");
    auto media = std::make_shared<MenuItem>("Media");

    auto displaySettings = std::make_shared<MenuItem>("Display Settings");
    auto audioSettings = std::make_shared<MenuItem>("Audio Settings");

    auto radio = std::make_shared<MenuItem>("Radio");
    auto bluetoothAudio = std::make_shared<MenuItem>("Bluetooth Audio");

    settings->addSubItem(displaySettings);
    settings->addSubItem(audioSettings);

    media->addSubItem(radio);
    media->addSubItem(bluetoothAudio);

    mainMenu->addSubItem(settings);
    mainMenu->addSubItem(media);

    // Creating the menu system and running it
    MenuSystem menuSystem(mainMenu);
    menuSystem.run();

    return 0;
}


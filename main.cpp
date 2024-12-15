#include <exception>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "van/van.hpp"
#include "train/train.hpp"

const std::vector<std::string> menu = {
    "Create van",
    "Create train",
    "Add van to train",
    "Remove van from train",
    "Show van",
    "Show train",
    "Sit passengers in the least occupied van",
    "Exit"
};

void printMenu(const std::vector<std::string>& menu) {
    for (size_t i = 0; i < menu.size(); ++i) {
        std::cout << i + 1 << ". " << menu[i] << std::endl;
    }
}

int main() {
    mgt::van currentVan;
    mgt::train currentTrain;
    bool vanCreated = false;
    bool trainCreated = false;

    while (true) {
        try {
            printMenu(menu);
            std::cout << ">>> ";
            size_t choice;
            std::cin >> choice;

            if (choice < 1 || choice > menu.size()) {
                throw std::invalid_argument("Invalid menu choice.");
            }

            switch (choice) {
                case 1: {
                    std::cout << "Enter van capacity, occupied seats, and type (restaurant, seated, economy, luxury):\n>>> ";
                    size_t capacity, occupied;
                    std::string typeStr;
                    std::cin >> capacity >> occupied >> typeStr;
                    if (!std::cin) throw std::invalid_argument("Invalid input format.");

                    mgt::van_type type = mgt::str_to_type.at(typeStr);
                    currentVan = mgt::van(capacity, occupied, type);
                    vanCreated = true;
                    std::cout << "Van created successfully!\n";
                    break;
                }
                case 2: {
                    currentTrain = mgt::train();
                    trainCreated = true;
                    std::cout << "Train created successfully!\n";
                    break;
                }
                case 3: {
                    if (!vanCreated || !trainCreated) throw std::invalid_argument("Van or train not created.");
                    currentTrain += currentVan;
                    std::cout << "Van added to train.\n";
                    break;
                }
                case 4: {
                    if (!trainCreated) throw std::invalid_argument("Train not created.");
                    std::cout << "Enter index of van to remove: ";
                    size_t index;
                    std::cin >> index;
                    currentTrain.deleteVan(index);
                    std::cout << "Van removed from train.\n";
                    break;
                }
                case 5: {
                    if (!vanCreated) throw std::invalid_argument("Van not created.");
                    std::cout << currentVan << std::endl;
                    break;
                }
                case 6: {
                    if (!trainCreated) throw std::invalid_argument("Train not created.");
                    std::cout << currentTrain << std::endl;
                    break;
                }
                case 7: {
                    if (!trainCreated) throw std::invalid_argument("Train not created.");
                    std::cout << "Enter number of passengers to sit: ";
                    size_t passengers;
                    std::cin >> passengers;
                    currentTrain.sitInMin(passengers);
                    std::cout << "Passengers seated successfully.\n";
                    break;
                }
                case 8:
                    std::cout << "Exiting...\n";
                    return 0;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        catch(const  std::exception&e){
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}

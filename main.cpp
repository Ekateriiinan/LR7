#include "game.h"
#include <iostream>

int main() {
    Game game;
    
    std::cout << "Инициализация игры..." << std::endl;
    game.initialize();
    
    std::cout << "Запуск игры на " << GameConfig::GAME_DURATION_SECONDS << " секунд..." << std::endl;
    game.run();
    
    std::cout << "Игра завершена!" << std::endl;
    
    return 0;
}
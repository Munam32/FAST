//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <cmath>
//#include <fstream>
//
//using namespace std;
//using namespace sf;
//
//void saveGame(int arr[5][5], bool player1Turn) {
//    ofstream outFile("savegame.txt");
//
//    if (outFile.is_open()) {
//        // Save the game state array
//        for (int i = 0; i < 5; i++) {
//            for (int j = 0; j < 5; j++) {
//                outFile << arr[i][j] << " ";
//            }
//            outFile << endl;
//        }
//
//        // Save the player turn
//        outFile << player1Turn << endl;
//
//        outFile.close();
//        cout << "Game Saved!" << endl;
//    }
//    else {
//        cerr << "Unable to open file for saving." << endl;
//    }
//}
//
//
//void loadGame(int arr[5][5], bool& player1Turn) {
//    ifstream inFile("savegame.txt");
//
//    if (inFile.is_open()) {
//        // Load the game state array
//        for (int i = 0; i < 5; i++) {
//            for (int j = 0; j < 5; j++) {
//                inFile >> arr[i][j];
//            }
//        }
//
//        // Load the player turn
//        inFile >> player1Turn;
//
//        inFile.close();
//        cout << "Game Loaded!" << endl;
//    }
//    else {
//        cerr << "Unable to open file for loading. Starting a new game." << endl;
//    }
//}
//
//int arr[5][5] = { {1, 1, 1, 1, 1},{1, 1, 1, 1, 1},{1, 1, 0, 2, 2},{2, 2, 2, 2, 2},{2, 2, 2, 2, 2} };
//bool player1Turn = true;
//
//void startGame(RenderWindow& window) {
//
//    sf::Texture greenWinTexture, redWinTexture;
//    if (!greenWinTexture.loadFromFile("red.png") || !redWinTexture.loadFromFile("green.png")) {
//        cerr << "Failed to load winning images!" << endl;
//
//    }
//
//    // Create sprites for winning images
//    sf::Sprite greenWinSprite(greenWinTexture);
//    sf::Sprite redWinSprite(redWinTexture);
//
//    Font font;
//    if (!font.loadFromFile("arial.ttf")) {
//        cerr << "Failed to load font!" << endl;
//    }
//
//
//    Text turnText;
//    turnText.setFont(font);
//    turnText.setCharacterSize(30);
//    turnText.setFillColor(player1Turn ? Color::Green : Color::Red);
//    turnText.setString(player1Turn ? "Player 1 Turn" : "Player 2 Turn");
//    turnText.setPosition(15.0f, 15.0f);
//
//    Text pauseText("Pause Game", font, 24);
//    pauseText.setPosition(350, 350);
//
//    bool paused = false;
//
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed)
//                window.close();
//            saveGame(arr, player1Turn);
//
//        }
//        RectangleShape Exit;
//        /*Exit.setPosition(150.0f);*/
//        Texture backgroundTexture;
//        if (!backgroundTexture.loadFromFile("bac.jpg")) {
//            cerr << "Failed to load background image" << endl;
//        }
//
//        Sprite backgroundSprite(backgroundTexture);
//
//        int move = 0;
//        int radius = 38;
//        int firstx = -1, firsty = -1, secondx = -1, secondy = -1;
//
//        while (window.isOpen())
//        {
//            Event event;
//            while (window.pollEvent(event)) {
//                if (event.type == Event::Closed) {
//                    window.close();
//                    saveGame(arr, player1Turn);
//                }
//                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
//
//
//                    Vector2i mousePos = Mouse::getPosition(window);
//                    window.clear();
//                    window.draw(backgroundSprite);
//                    for (int i = 0; i < 5; i++) {
//                        for (int j = 0; j < 5; j++) {
//                            float centerX = 190 * j + 95;
//                            float centerY = 190 * i + 95;
//                            float distance = sqrt(pow(mousePos.x - centerX, 2) + pow(mousePos.y - centerY, 2));
//
//                            if (distance <= radius) {
//                                if (firstx == -1 && firsty == -1) {
//                                    firstx = i;
//                                    firsty = j;
//                                }
//                                else if (secondx == -1 && secondy == -1) {
//                                    secondx = i;
//                                    secondy = j;
//
//                                    if (move % 2 != 0) {
//                                        // Vertical and Horizontal Movement of Red Beads
//                                        if ((arr[firstx][firsty] == 1 && arr[secondx][secondy] == 0) && ((firstx == secondx && firsty == secondy - 1) || (firstx == secondx + 1 && firsty == secondy) || (firstx == secondx && firsty == secondy + 1) || (firstx == secondx - 1 && firsty == secondy))) {
//
//                                            cout << "You clicked  first circle on (" << firstx << ", " << firsty << ")" << endl;
//                                            cout << "You clicked the second circle at (" << secondx << ", " << secondy << ")" << endl;
//
//                                            int temp = arr[firstx][firsty];
//                                            arr[firstx][firsty] = arr[secondx][secondy];
//                                            arr[secondx][secondy] = temp;
//                                            move++;
//                                            cout << "Swapped circles at (" << firstx << ", " << firsty << ") and (" << secondx << ", " << secondy << ")" << endl;
//
//                                            player1Turn = !player1Turn; // Make sure this is in the correct place in your code
//                                            turnText.setFillColor(player1Turn ? Color::Green : Color::Red);
//                                            turnText.setString(player1Turn ? "Player 1 Turn" : "Player 2 Turn");
//
//                                        }
//
//                                        // Eliminating Green Beads by Vertical and Horizontal Movement
//                                        else if ((arr[firstx][firsty] == 1 && arr[secondx][secondy] == 0 && arr[(firstx + secondx) / 2][(firsty + secondy) / 2] == 2) && ((firstx == secondx && firsty == secondy - 2) || (firstx == secondx + 2 && firsty == secondy) || (firstx == secondx && firsty == secondy + 2) || (firstx == secondx - 2 && firsty == secondy))) {
//
//                                            arr[(firstx + secondx) / 2][(firsty + secondy) / 2] = 0;
//                                            cout << "You clicked  first circle on (" << firstx << ", " << firsty << ")" << endl;
//                                            cout << "You clicked the second circle at (" << secondx << ", " << secondy << ")" << endl;
//                                            int temp = arr[firstx][firsty];
//                                            arr[firstx][firsty] = arr[secondx][secondy];
//                                            arr[secondx][secondy] = temp;
//                                            move++;
//                                            cout << "Swapped circles at (" << firstx << ", " << firsty << ") and (" << secondx << ", " << secondy << ")" << endl;
//                                            player1Turn = !player1Turn; // Make sure this is in the correct place in your code
//                                            turnText.setFillColor(player1Turn ? Color::Green : Color::Red);
//                                            turnText.setString(player1Turn ? "Player 1 Turn" : "Player 2 Turn");
//
//                                        }
//
//                                        // Diagonal movement of Red Beads
//                                        else if ((firstx % 2 == 0 && firsty % 2 == 0) || (firstx % 2 == 1 && firsty % 2 == 1)) {
//                                            if ((arr[firstx][firsty] == 1 && arr[secondx][secondy] == 0) && ((firstx == secondx + 1 && firsty == secondy - 1) || (firstx == secondx + 1 && firsty == secondy + 1) || (firstx == secondx - 1 && firsty == secondy + 1) || (firstx == secondx - 1 && firsty == secondy - 1))) {
//
//                                                cout << "You clicked  first circle on(" << firstx << ", " << firsty << ")" << endl;
//                                                cout << "You clicked  second circle on (" << secondx << ", " << secondy << ")" << endl;
//                                                int temp = arr[firstx][firsty];
//                                                arr[firstx][firsty] = arr[secondx][secondy];
//                                                arr[secondx][secondy] = temp;
//                                                move++;
//                                                cout << "Swapped circles at (" << firstx << ", " << firsty << ") and (" << secondx << ", " << secondy << ")" << endl;
//                                                player1Turn = !player1Turn; // Make sure this is in the correct place in your code
//                                                turnText.setFillColor(player1Turn ? Color::Green : Color::Red);
//                                                turnText.setString(player1Turn ? "Player 1 Turn" : "Player 2 Turn");
//
//                                            }
//                                            // Eliminating Green Beads by Diagonal Movement
//                                            if ((arr[firstx][firsty] == 1 && arr[secondx][secondy] == 0 && arr[(firstx + secondx) / 2][(firsty + secondy) / 2] == 2) && ((firstx == secondx + 2 && firsty == secondy - 2) || (firstx == secondx + 2 && firsty == secondy + 2) || (firstx == secondx - 2 && firsty == secondy + 2) || (firstx == secondx - 2 && firsty == secondy - 2))) {
//
//                                                arr[(firstx + secondx) / 2][(firsty + secondy) / 2] = 0;
//                                                cout << "You clicked  first circle on (" << firstx << ", " << firsty << ")" << endl;
//                                                cout << "You clicked  second circle on (" << secondx << ", " << secondy << ")" << endl;
//                                                int temp = arr[firstx][firsty];
//                                                arr[firstx][firsty] = arr[secondx][secondy];
//                                                arr[secondx][secondy] = temp;
//                                                move++;
//                                                cout << "Swapped circles at (" << firstx << ", " << firsty << ") and (" << secondx << ", " << secondy << ")" << endl;
//                                                player1Turn = !player1Turn; // Make sure this is in the correct place in your code
//                                                turnText.setFillColor(player1Turn ? Color::Green : Color::Red);
//                                                turnText.setString(player1Turn ? "Player 1 Turn" : "Player 2 Turn");
//                                            }
//                                        }
//                                        else cout << "Invalid Move." << endl;
//                                    }
//
//                                    else if (move % 2 == 0) {
//                                        // Vertical and Horizontal Movement of Green Beads
//                                        if ((arr[firstx][firsty] == 2 && arr[secondx][secondy] == 0) && ((firstx == secondx && firsty == secondy - 1) || (firstx == secondx + 1 && firsty == secondy) || (firstx == secondx && firsty == secondy + 1) || (firstx == secondx - 1 && firsty == secondy))) {
//
//                                            cout << "You clicked  first circle on (" << firstx << ", " << firsty << ")" << endl;
//                                            cout << "You clicked  second circle on (" << secondx << ", " << secondy << ")" << endl;
//
//                                            int temp = arr[firstx][firsty];
//                                            arr[firstx][firsty] = arr[secondx][secondy];
//                                            arr[secondx][secondy] = temp;
//                                            move++;
//                                            cout << "Swapped circles at (" << firstx << ", " << firsty << ") and (" << secondx << ", " << secondy << ")" << endl;
//                                            player1Turn = !player1Turn; // Make sure this is in the correct place in your code
//                                            turnText.setFillColor(player1Turn ? Color::Green : Color::Red);
//                                            turnText.setString(player1Turn ? "Player 1 Turn" : "Player 2 Turn");
//                                        }
//                                        // Eliminating Red Beads by Vertical and Horizontal Movement
//                                        else if ((arr[firstx][firsty] == 2 && arr[secondx][secondy] == 0 && arr[(firstx + secondx) / 2][(firsty + secondy) / 2] == 1) && ((firstx == secondx && firsty == secondy - 2) || (firstx == secondx + 2 && firsty == secondy) || (firstx == secondx && firsty == secondy + 2) || (firstx == secondx - 2 && firsty == secondy))) {
//
//                                            arr[(firstx + secondx) / 2][(firsty + secondy) / 2] = 0;
//                                            cout << "You clicked  first circle on (" << firstx << ", " << firsty << ")" << endl;
//                                            cout << "You clicked  second circle on (" << secondx << ", " << secondy << ")" << endl;
//                                            int temp = arr[firstx][firsty];
//                                            arr[firstx][firsty] = arr[secondx][secondy];
//                                            arr[secondx][secondy] = temp;
//                                            move++;
//                                            cout << "Swap circles on (" << firstx << ", " << firsty << ") and (" << secondx << ", " << secondy << ")" << endl;
//                                            player1Turn = !player1Turn; // Make sure this is in the correct place in your code
//                                            turnText.setFillColor(player1Turn ? Color::Green : Color::Red);
//                                            turnText.setString(player1Turn ? "Player 1 Turn" : "Player 2 Turn");
//                                        }
//
//                                        // Diagonal movement of Green Beads
//                                        else if ((firstx % 2 == 0 && firsty % 2 == 0) || (firstx % 2 == 1 && firsty % 2 == 1)) {
//                                            if ((arr[firstx][firsty] == 2 && arr[secondx][secondy] == 0) && ((firstx == secondx + 1 && firsty == secondy - 1) || (firstx == secondx + 1 && firsty == secondy + 1) || (firstx == secondx - 1 && firsty == secondy + 1) || (firstx == secondx - 1 && firsty == secondy - 1))) {
//
//                                                cout << "You clicked  first circle on (" << firstx << ", " << firsty << ")" << endl;
//                                                cout << "You clicked  second circle on (" << secondx << ", " << secondy << ")" << endl;
//                                                int temp = arr[firstx][firsty];
//                                                arr[firstx][firsty] = arr[secondx][secondy];
//                                                arr[secondx][secondy] = temp;
//                                                move++;
//                                                cout << "Swapped circles at (" << firstx << ", " << firsty << ") and (" << secondx << ", " << secondy << ")" << endl;
//                                                player1Turn = !player1Turn; // Make sure this is in the correct place in your code
//                                                turnText.setFillColor(player1Turn ? Color::Green : Color::Red);
//                                                turnText.setString(player1Turn ? "Player 1 Turn" : "Player 2 Turn");
//                                            }
//                                            // Eliminating Red Beads by Diagonal Movement
//                                            if ((arr[firstx][firsty] == 2 && arr[secondx][secondy] == 0 && arr[(firstx + secondx) / 2][(firsty + secondy) / 2] == 1) && ((firstx == secondx + 2 && firsty == secondy - 2) || (firstx == secondx + 2 && firsty == secondy + 2) || (firstx == secondx - 2 && firsty == secondy + 2) || (firstx == secondx - 2 && firsty == secondy - 2))) {
//
//                                                arr[(firstx + secondx) / 2][(firsty + secondy) / 2] = 0;
//                                                cout << "You clicked  first circle on (" << firstx << ", " << firsty << ")" << endl;
//                                                cout << "You clicked  second circle on (" << secondx << ", " << secondy << ")" << endl;
//                                                int temp = arr[firstx][firsty];
//                                                arr[firstx][firsty] = arr[secondx][secondy];
//                                                arr[secondx][secondy] = temp;
//                                                move++;
//                                                cout << "Swapped circles at (" << firstx << ", " << firsty << ") and (" << secondx << ", " << secondy << ")" << endl;
//                                                player1Turn = !player1Turn; // Make sure this is in the correct place in your code
//                                                turnText.setFillColor(player1Turn ? Color::Green : Color::Red);
//                                                turnText.setString(player1Turn ? "Player 1 Turn" : "Player 2 Turn");
//                                            }
//                                        }
//                                        else cout << "Invalid Move" << endl;
//                                    }
//                                    else cout << "Invaid Move" << endl;
//
//                                    firstx = -1;
//                                    firsty = -1;
//                                    secondx = -1;
//                                    secondy = -1;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//
//            bool redflag = true;
//            for (int i = 0; i < 5; i++) {
//                for (int j = 0; j < 5; j++) {
//                    if (arr[i][j] == 1) redflag = false;
//                }
//            }
//            if (redflag) {
//                if (redflag) {
//                    window.draw(redWinSprite);
//                    window.display();
//                    
//                    sf::sleep(sf::seconds(5)); // Sleep for 5 seconds
//                    window.close();
//                }
//                
//
//                cout << endl << endl;
//                cout << "o-" << "-------------------" << "-o" << endl;
//                cout << "| " << " Congratulations   " << " |" << endl;
//                cout << "| " << "GREEN WON THE GAME!" << " |" << endl;
//                cout << "| " << "                   " << " |" << endl;
//                cout << "|_" << "<<<<<GAME END>>>>>>" << "_|" << endl;
//                break;
//            }
//
//            bool greenflag = true;
//            for (int i = 0; i < 5; i++) {
//                for (int j = 0; j < 5; j++) {
//                    if (arr[i][j] == 2) greenflag = false;
//                }
//            }
//            if (greenflag) {
//                if (greenflag) {
//                    window.draw(greenWinSprite);
//                    window.display();
//                    
//                    sf::sleep(sf::seconds(5)); // Sleep for 5 seconds
//                    window.close();
//                }
//                
//                cout << endl << endl;
//                cout << "o-" << "-----------------" << "-o" << endl;
//                cout << "| " << "Congratulations  " << " |" << endl;
//                cout << "| " << "RED WON THE GAME!" << " |" << endl;
//                cout << "| " << "                 " << " |" << endl;
//                cout << "|_" << "<<<<<GAME END>>>>>" << "_|" << endl;
//                break;
//            }
//
//            window.clear();
//            window.draw(backgroundSprite);
//
//            for (int i = 0; i < 5; i++) {
//                for (int j = 0; j < 5; j++) {
//                    CircleShape circle(radius);
//                    circle.setPosition(190 * j + 57, 190 * i + 57);
//
//                    if (arr[i][j] == 1) {
//                        circle.setFillColor(Color::Red);
//                    }
//                    else if (arr[i][j] == 2) {
//                        circle.setFillColor(Color::Green);
//                    }
//                    else if (arr[i][j] == 0) {
//                        circle.setFillColor(Color::White);
//                    }
//
//                    circle.setOutlineColor(Color::Black);
//                    circle.setOutlineThickness(5);
//
//                    window.draw(circle);
//                }
//            }
//            window.draw(turnText);
//            window.display();
//        }
//
//        system("pause");
//
//        // Draw the game state, update UI, etc.
//        // ...
//    }
//}
//
//bool isButtonClicked(const RectangleShape& button, const Vector2i& mousePos) {
//    return button.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));
//}
//
//int main() {
//    RenderWindow window(VideoMode(949, 945), "Menu");
//
//    RectangleShape continueBtn(Vector2f(200, 50));
//    continueBtn.setPosition(375, 300);
//    continueBtn.setFillColor(Color::Blue);
//
//    RectangleShape newGameBtn(Vector2f(200, 50));
//    newGameBtn.setPosition(375, 400);
//    newGameBtn.setFillColor(Color::Green);
//
//    RectangleShape quitBtn(Vector2f(200, 50));
//    quitBtn.setPosition(375, 500);
//    quitBtn.setFillColor(Color::Red);
//
//    Font font;
//    if (!font.loadFromFile("arial.ttf")) {
//        cerr << "Failed to load font!" << endl;
//        return EXIT_FAILURE;
//    }
//
//    Text continueText("Continue Game", font, 20);
//    continueText.setPosition(continueBtn.getPosition().x + 20, continueBtn.getPosition().y + 10);
//    continueText.setFillColor(Color::White);
//
//    Text newGameText("New Game", font, 20);
//    newGameText.setPosition(newGameBtn.getPosition().x + 50, newGameBtn.getPosition().y + 10);
//    newGameText.setFillColor(Color::White);
//
//    Text quitText("Quit", font, 20);
//    quitText.setPosition(quitBtn.getPosition().x + 80, quitBtn.getPosition().y + 10);
//    quitText.setFillColor(Color::White);
//
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed)
//                window.close();
//
//            if (event.type == Event::MouseButtonPressed) {
//                Vector2i mousePos = Mouse::getPosition(window);
//                if (isButtonClicked(continueBtn, mousePos)) {
//                    // Load the saved game and start
//                    loadGame(arr, player1Turn);
//                    startGame(window);
//                }
//                else if (isButtonClicked(newGameBtn, mousePos)) {
//                    // Start a new game
//                    startGame(window);
//                }
//                else if (isButtonClicked(quitBtn, mousePos)) {
//                    // Quit the program
//                    window.close();
//                }
//            }
//        }
//
//        window.clear();
//
//        // Draw buttons
//        window.draw(continueBtn);
//        window.draw(continueText);
//        window.draw(newGameBtn);
//        window.draw(newGameText);
//        window.draw(quitBtn);
//        window.draw(quitText);
//
//        window.display();
//    }
//
//    return 0;
//}

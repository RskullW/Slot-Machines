#pragma once 
struct PlayerStatics {
public:
    int Money;
    
    PlayerStatics() {
        Money = 200;
    }
    
    PlayerStatics(int money) {
        Money = money;
    }
};
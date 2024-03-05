#pragma once

#include <iostream>
#include "Observer.h"

class IDeathAgregator {
    protected:
        virtual void attach(IObserver* observer) = 0;
        virtual void detach(IObserver* observer) = 0;
        virtual void notify(INPC* npc) = 0;
};

class DeathAgregator : public IDeathAgregator {
    private:
        std::vector<IObserver*> observers;
    public:
        void attach(IObserver* observer) override { 
            observers.push_back(observer); 
        }
        void detach(IObserver* observer) override {
            int n = static_cast<int>(observers.size());
            int index = -1;
            for (int i = 0; i < n; ++i) {
                if(observers[i] == observer) {
                    index = i;
                }
            }
            if (index != -1) {
                std::swap(observers[n - 1], observers[index]);
            }
            observers.resize(n - 1);
        }
        void notify(INPC* npc) override {
            for (auto& observer : observers) {
                observer->update(npc);
            }
        }
};
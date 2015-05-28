#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H


class gameStateManager
{
    public:
        gameStateManager();
        virtual ~gameStateManager();
        void setState(int value);
        int getState();
    protected:
    private:
        int state;
};

#endif // GAMESTATEMANAGER_H

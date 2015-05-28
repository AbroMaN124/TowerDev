#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H


class sceneManager
{
    public:
        static sceneManager& getInstance() {
            static sceneManager instance;
            return instance;
        }
    protected:
    private:
        sceneManager();
};

#endif // SCENEMANAGER_H

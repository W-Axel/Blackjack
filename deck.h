#include <vector>
#include <memory>
#include <algorithm>
#include <random>

class Deck
{
    private:
        std::shared_ptr<std::vector<int>> cards_ptr = std::make_shared<std::vector<int>>();
    public:
        Deck();
        void reset();
        int size();
        int pullCard();
};
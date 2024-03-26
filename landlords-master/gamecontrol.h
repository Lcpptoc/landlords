#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "robot.h"
#include "userplayer.h"
#include "cards.h"

struct BetRecord
{
    BetRecord()
    {
        reset();
    }
    void reset()
    {
        player = nullptr;
        bet = 0;
        times = 0;
    }
    Player* player;
    int bet;
    int times;
};

class GameControl : public QObject
{
    Q_OBJECT
public:
    enum GameStatus
    {
        DispatchCard,
        CallingLord,
        PlayingHand
    };
    enum PlayerStatus
    {
        ThinkingForCallLord,
        ThinkingForPlayHand,
        Winning
    };

    explicit GameControl(QObject *parent = nullptr);

    void playerInit();

    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUserPlayer();

    void setCurrentPlayer(Player* player);
    Player* getCurrentPlayer();

    //得到玩家和打出去的牌
    Player* getPendPlayer();
    Cards getPendCards();

    //初始化扑克牌
    void initAllCards();
    //得到一张牌
    Card takeOneCard();
    //得到最后三张牌
    Cards getSurplusCards();
    //重置卡牌数据
    void resetCardData();

    //开始叫地主
    void startLordCard();
    //成为地主
    void becomeLord(Player *player, int bet);
    void clearPlayerScore();
    int getPlayerMaxBet();

    void onGrabBet(Player* player, int bet);

    void onPlayHand(Player *player, const Cards &card);

signals:
    void playerStatusChanged(Player* player, PlayerStatus status);
    void notifyGrabLordBet(Player* player, int bet, bool flag);
    void gameStatusChanged(GameStatus status);
    void notifyPlayHand(Player* player, const Cards& card);
    void pendingInfo(Player* player, const Cards& card);

private:
    Robot* m_robotLeft = nullptr;
    Robot* m_robotRight = nullptr;
    UserPlayer* m_user = nullptr;
    Player* m_currPlayer = nullptr;
    Player* m_pendPlayer = nullptr;
    Cards m_pendCards;
    Cards m_allCards;
    BetRecord m_betRecord;
    int m_curBet = 0;

};

#endif // GAMECONTROL_H

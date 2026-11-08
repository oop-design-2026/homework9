/*
 * Problem 2: RTTI & dynamic_cast
 *
 * 학번:
 * 이름:
 *
 * ─────────────────────────────────────────────────────────────
 * 아래 runner 함수(runProblem2)가 올바르게 동작하도록
 * identifyAndCast 와 safeRefCast 함수를 직접 구현하세요.
 * Character, Knight, Wizard 클래스는 이미 제공되어 있습니다.
 * 수정하지 마세요.
 *
 *
 * [identifyAndCast 동작]
 *   (1) typeid 로 c 의 실제 타입을 비교하여 아래를 출력하세요.
 *         Knight 이면: "[typeid] Type: Knight"
 *         Wizard 이면: "[typeid] Type: Wizard"
 *   (2) dynamic_cast<Knight*>(c) 를 시도하세요.
 *         성공(non-null) 이면: "[dynamic_cast] Knight*: SUCCESS" 출력 후 challenge() 호출
 *         실패(nullptr)   이면: "[dynamic_cast] Knight*: FAILED (nullptr)" 출력
 *   (3) dynamic_cast<Wizard*>(c) 를 시도하세요.
 *         성공(non-null) 이면: "[dynamic_cast] Wizard*: SUCCESS" 출력 후 reveal() 호출
 *         실패(nullptr)   이면: "[dynamic_cast] Wizard*: FAILED (nullptr)" 출력
 *
 * [safeRefCast 동작]
 *   (1) dynamic_cast<Knight&>(c) 를 try 블록에서 시도하세요.
 *         성공: "[ref cast] Knight&: SUCCESS" 출력 후 challenge() 호출
 *         bad_cast: "[ref cast] Knight&: bad_cast caught" 출력
 *   (2) dynamic_cast<Wizard&>(c) 를 try 블록에서 시도하세요.
 *         성공: "[ref cast] Wizard&: SUCCESS" 출력 후 reveal() 호출
 *         bad_cast: "[ref cast] Wizard&: bad_cast caught" 출력
 *
 * runner 함수(runProblem2)는 수정하지 마세요.
 * ─────────────────────────────────────────────────────────────
 */
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

namespace {

// ── Character (제공됨, 수정하지 마세요) ────────────────────────
class Character {
protected:
    string name;
    int hp;
public:
    Character(const string& name, int hp) : name(name), hp(hp) {}
    virtual string getType() const = 0;
    virtual ~Character() = default;
    string getName() const { return name; }
};

// ── Knight (제공됨, 수정하지 마세요) ───────────────────────────
class Knight : public Character {
    int swordLevel;
public:
    Knight(const string& name, int hp, int swordLevel)
        : Character(name, hp), swordLevel(swordLevel) {}
    string getType() const override { return "Knight"; }
    void challenge() const {
        cout << "Knight " << name << " challenges you to a duel!" << "\n";
    }
};

// ── Wizard (제공됨, 수정하지 마세요) ───────────────────────────
class Wizard : public Character {
    int manaPool;
public:
    Wizard(const string& name, int hp, int manaPool)
        : Character(name, hp), manaPool(manaPool) {}
    string getType() const override { return "Wizard"; }
    void reveal() const {
        cout << "Wizard " << name << " reveals the secrets of the arcane!" << "\n";
    }
};

// ── identifyAndCast 를 구현하세요 ──────────────────────────────
// typeid 로 c 의 실제 타입을 확인하고,
// dynamic_cast (포인터) 로 안전하게 Downcast 하여 고유 메서드를 호출하세요.
void identifyAndCast(Character* c) {
    // TODO (1): typeid(*c) 와 typeid(Knight), typeid(Wizard) 를 비교하여 타입을 출력하세요.

    // TODO (2): dynamic_cast<Knight*>(c) 를 시도하고 결과에 따라 출력하세요.

    // TODO (3): dynamic_cast<Wizard*>(c) 를 시도하고 결과에 따라 출력하세요.
}

// ── safeRefCast 를 구현하세요 ──────────────────────────────────
// dynamic_cast (레퍼런스) 로 안전하게 Downcast 하고,
// 실패 시 발생하는 std::bad_cast 를 처리하세요.
void safeRefCast(Character& c) {
    // TODO (1): try { dynamic_cast<Knight&>(c) } catch (bad_cast) 로 처리하세요.

    // TODO (2): try { dynamic_cast<Wizard&>(c) } catch (bad_cast) 로 처리하세요.
}

} // namespace

// ── runner (수정하지 마세요) ───────────────────────────────────
void runProblem2(istream& in) {
    string kName, wName;
    int kHp, kSword, wHp, wMana;
    in >> kName >> kHp >> kSword >> wName >> wHp >> wMana;

    cout << "=== Problem 2: RTTI & dynamic_cast ===" << "\n";

    Character* party[2];
    party[0] = new Knight(kName, kHp, kSword);
    party[1] = new Wizard(wName, wHp, wMana);

    cout << "[Part 1] typeid + dynamic_cast (pointer)" << "\n";
    for (int i = 0; i < 2; i++) {
        cout << "--- party[" << i << "] ---" << "\n";
        identifyAndCast(party[i]);
    }

    cout << "[Part 2] dynamic_cast (reference) + bad_cast" << "\n";
    for (int i = 0; i < 2; i++) {
        cout << "--- party[" << i << "] ---" << "\n";
        safeRefCast(*party[i]);
    }

    for (int i = 0; i < 2; i++) delete party[i];
}
// ─────────────────────────────────────────────────────────────

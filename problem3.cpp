/*
 * Problem 3: Type Confusion
 *
 * 학번:
 * 이름:
 *
 * ─────────────────────────────────────────────────────────────
 * 아래 runner 함수(runProblem3)가 올바르게 동작하도록
 * Warrior, Mage 클래스와 analyzeConfusion, safeDispatch 함수를
 * 직접 구현하세요.
 * Entity 클래스는 이미 제공되어 있습니다. 수정하지 마세요.
 *
 *
 * [Warrior 출력 형식]
 *   getType() → "Warrior"
 *   slash()   → "Warrior <name> slashes the enemy for <power> damage!"
 *
 * [Mage 출력 형식]
 *   getType() → "Mage"
 *   chant()   → "Mage <name> chants a spell with <mana> mana!"
 *
 * [analyzeConfusion 동작]
 *   (1) static_cast<Warrior*>(e) 를 시도하세요.
 *         결과가 non-null 이면: "[static_cast] Warrior*: non-null (type not checked)"
 *   (2) static_cast<Mage*>(e) 를 시도하세요.
 *         결과가 non-null 이면: "[static_cast] Mage*: non-null (type not checked)"
 *         ※ (1)(2) 모두 항상 non-null — 이것이 Type Confusion 의 원인입니다.
 *            실제로 메서드를 호출하지 마세요. (Undefined Behavior)
 *   (3) dynamic_cast<Warrior*>(e) 를 시도하세요.
 *         성공: "[dynamic_cast] Warrior*: SUCCESS"
 *         실패: "[dynamic_cast] Warrior*: nullptr"
 *   (4) dynamic_cast<Mage*>(e) 를 시도하세요.
 *         성공: "[dynamic_cast] Mage*: SUCCESS"
 *         실패: "[dynamic_cast] Mage*: nullptr"
 *
 * [safeDispatch 동작]
 *   - dynamic_cast 로 실제 타입을 확인한 뒤 적절한 메서드를 호출하세요.
 *   - Warrior 이면 slash(), Mage 이면 chant() 를 호출하세요.
 *   - 알 수 없는 타입이면 "Unknown entity type" 을 출력하세요.
 *
 * runner 함수(runProblem3)는 수정하지 마세요.
 * ─────────────────────────────────────────────────────────────
 */
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

namespace {

// ── Entity (제공됨, 수정하지 마세요) ───────────────────────────
class Entity {
protected:
    string name;
    int power;
public:
    Entity(const string& name, int power) : name(name), power(power) {}
    virtual string getType() const = 0;
    virtual ~Entity() = default;
};

// ── Warrior 를 구현하세요 ───────────────────────────────────────
// 추가 메서드: slash()
class Warrior /* : public Entity */ {
    // TODO
};

// ── Mage 를 구현하세요 ─────────────────────────────────────────
// 추가 메서드: chant()
class Mage /* : public Entity */ {
    // TODO
};

// ── analyzeConfusion 을 구현하세요 ─────────────────────────────
// static_cast 와 dynamic_cast 의 동작 차이를 직접 비교하세요.
// 타입이 맞지 않는 static_cast 결과로 메서드를 호출하지 마세요. (UB)
void analyzeConfusion(Entity* e) {
    // TODO (1): static_cast<Warrior*>(e) 를 시도하고 non-null 여부를 출력하세요.

    // TODO (2): static_cast<Mage*>(e) 를 시도하고 non-null 여부를 출력하세요.

    // TODO (3): dynamic_cast<Warrior*>(e) 를 시도하고 결과를 출력하세요.

    // TODO (4): dynamic_cast<Mage*>(e) 를 시도하고 결과를 출력하세요.
}

// ── safeDispatch 를 구현하세요 ─────────────────────────────────
// dynamic_cast 로 실제 타입을 확인한 후 올바른 메서드를 호출하세요.
void safeDispatch(Entity* e) {
    // TODO: Warrior 이면 slash(), Mage 이면 chant(), 그 외 "Unknown entity type"
}

} // namespace

// ── runner (수정하지 마세요) ───────────────────────────────────
void runProblem3(istream& in) {
    string wName, mName;
    int wPow, mMana;
    in >> wName >> wPow >> mName >> mMana;

    cout << "=== Problem 3: Type Confusion ===" << "\n";

    Entity* p1 = new Warrior(wName, wPow);
    Entity* p2 = new Mage(mName, mMana);

    cout << "[Part 1] analyzeConfusion: static_cast vs dynamic_cast" << "\n";
    cout << "--- p1 (Warrior) ---" << "\n";
    analyzeConfusion(p1);
    cout << "--- p2 (Mage) ---" << "\n";
    analyzeConfusion(p2);

    cout << "[Part 2] safeDispatch: dynamic_cast in action" << "\n";
    safeDispatch(p1);
    safeDispatch(p2);

    delete p1;
    delete p2;
}
// ─────────────────────────────────────────────────────────────

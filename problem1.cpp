/*
 * Problem 1: Downcasting
 *
 * 학번:
 * 이름:
 *
 * ─────────────────────────────────────────────────────────────
 * 아래 runner 함수(runProblem1)가 올바르게 동작하도록
 * Knight, Wizard 클래스와 performCasting, showWrongCasting 함수를
 * 직접 구현하세요.
 * Character 클래스는 이미 제공되어 있습니다. 수정하지 마세요.ㅈ
 *
 *
 * [Knight 출력 형식]
 *   describe()          → "Knight <name> (HP:<hp>, SwordLv:<swordLevel>)"
 *   getType()           → "Knight"
 *   knightCharge(times) → "Knight <name> charges <times> times with sword (Lv.<swordLevel>)!"
 *
 * [Wizard 출력 형식]
 *   describe()     → "Wizard <name> (HP:<hp>, Mana:<manaPool>)"
 *   getType()      → "Wizard"
 *   castUltimate() → "Wizard <name> unleashes a spell consuming <manaPool> mana!"
 *
 * [performCasting 동작]
 *   - static_cast 를 이용하여 p1 을 Knight* 로 변환한 후 knightCharge(times) 를 호출하세요.
 *   - static_cast 를 이용하여 p2 를 Wizard* 로 변환한 후 castUltimate() 를 호출하세요.
 *
 * [showWrongCasting 동작]
 *   - static_cast 를 이용하여 p1(Knight 객체) 을 Wizard* 로 잘못 변환하세요.
 *   - 반환된 포인터가 non-null 임을 확인하세요. (static_cast 는 타입을 검사하지 않는다!)
 *   - dynamic_cast 로 같은 변환을 시도하여 nullptr 가 반환됨을 확인하세요.
 *   - 아래 형식으로 출력하세요:
 *       "[Wrong] static_cast<Wizard*>(p1) returned non-null — static_cast has no type check!\n"
 *       "[!!] Calling wrong->castUltimate() would be Undefined Behavior!\n"
 *       "[Safe] dynamic_cast<Wizard*>(p1) returned nullptr\n"
 *
 * runner 함수(runProblem1)는 수정하지 마세요.
 * ─────────────────────────────────────────────────────────────
 */
#include <iostream>
#include <string>
using namespace std;

namespace {

// ── Character (제공됨, 수정하지 마세요) ────────────────────────
class Character {
protected:
    string name;
    int hp;
public:
    Character(const string& name, int hp) : name(name), hp(hp) {}
    virtual void describe() const = 0;
    virtual string getType() const = 0;
    virtual ~Character() = default;
    string getName() const { return name; }
    int getHp() const { return hp; }
};

// ── Knight 를 구현하세요 ────────────────────────────────────────
// 추가 멤버: swordLevel (int)
// 추가 메서드: knightCharge(int times)
class Knight /* : public Character */ {
    // TODO
};

// ── Wizard 를 구현하세요 ────────────────────────────────────────
// 추가 멤버: manaPool (int)
// 추가 메서드: castUltimate()
class Wizard /* : public Character */ {
    // TODO
};

// ── performCasting 을 구현하세요 ───────────────────────────────
// p1(Knight 객체), p2(Wizard 객체) 를 올바르게 Downcast 하여
// 각 클래스의 고유 메서드를 호출하세요.
void performCasting(Character* p1, Character* p2, int times) {
    // TODO: static_cast 로 p1 → Knight*, knightCharge(times) 호출

    // TODO: static_cast 로 p2 → Wizard*, castUltimate() 호출
}

// ── showWrongCasting 을 구현하세요 ─────────────────────────────
// p1(Knight 객체) 을 Wizard* 로 잘못 Downcast 했을 때의 위험성을 확인하세요.
// wrong->castUltimate() 는 절대 호출하지 마세요. (Undefined Behavior)
void showWrongCasting(Character* p1) {
    // TODO: static_cast 로 p1 → Wizard* (잘못된 변환)
    //       반환된 포인터가 non-null 임을 확인하고 아래를 출력하세요.
    //       "[Wrong] static_cast<Wizard*>(p1) returned non-null — static_cast has no type check!"

    // TODO: wrong->castUltimate() 를 호출하면 UB 임을 주석으로 명시하고 아래를 출력하세요.
    //       "[!!] Calling wrong->castUltimate() would be Undefined Behavior!"

    // TODO: dynamic_cast 로 같은 변환을 시도하여 nullptr 를 확인하고 아래를 출력하세요.
    //       "[Safe] dynamic_cast<Wizard*>(p1) returned nullptr"
}

} // namespace

// ── runner (수정하지 마세요) ───────────────────────────────────
void runProblem1(istream& in) {
    string kName, wName;
    int kHp, kSword, chargeCount, wHp, wMana;
    in >> kName >> kHp >> kSword >> chargeCount >> wName >> wHp >> wMana;

    cout << "=== Problem 1: Downcasting ===" << "\n";

    // Upcasting: Base Class Pointer 로 Derived Object 를 참조
    Character* p1 = new Knight(kName, kHp, kSword);
    Character* p2 = new Wizard(wName, wHp, wMana);

    cout << "[Part 1] Upcasting: Base Class Pointer" << "\n";
    p1->describe();
    p2->describe();

    // Correct Downcasting: 올바른 타입으로 변환 → Derived Class 고유 메서드 호출
    cout << "[Part 2] Correct Downcasting (static_cast)" << "\n";
    performCasting(p1, p2, chargeCount);

    // Wrong Downcasting: p1(Knight) 을 Wizard* 로 변환하면 어떻게 될까?
    cout << "[Part 3] Wrong Downcasting: Undefined Behavior Risk" << "\n";
    showWrongCasting(p1);

    delete p1;
    delete p2;
}
// ─────────────────────────────────────────────────────────────

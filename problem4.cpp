/*
 * Problem 4: Strategy Pattern
 * 학번:
 * 이름:
 *
 */
#include <iostream>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════
// [BAD] 수정하지 마세요 — 문제점을 파악한 뒤 아래 GOOD 을 구현하세요
// ════════════════════════════════════════════════════════════════
class BadCharacter {
protected:
    string name;
    string attackType;
public:
    BadCharacter(const string& n, const string& t) : name(n), attackType(t) {}
    virtual ~BadCharacter() = default;
    void attack() const {
        if (attackType == "sword")       cout << name << " swings a Sword!" << "\n";
        else if (attackType == "magic")  cout << name << " casts a Magic spell!" << "\n";
        else if (attackType == "bow")    cout << name << " shoots a Bow!" << "\n";
        // 새 공격 추가 → 이 함수 직접 수정 필요, 런타임 변경 불가
    }
};
class BadKnight : public BadCharacter {
public: explicit BadKnight(const string& n) : BadCharacter(n, "sword") {}
};
class BadWizard : public BadCharacter {
public: explicit BadWizard(const string& n) : BadCharacter(n, "magic") {}
};
class BadArcher : public BadCharacter {
public: explicit BadArcher(const string& n) : BadCharacter(n, "bow") {}
};

// ════════════════════════════════════════════════════════════════
// [GOOD] 여기서부터 구현하세요
// main() 을 보고 Strategy Pattern 을 직접 설계하세요.
//   - 공격 행동을 캡슐화하는 인터페이스를 만드세요.
//   - 캐릭터가 그 인터페이스의 포인터를 HAS-A 로 보유하게 하세요.
//   - setAttackStrategy() 로 런타임에 교체 가능하게 하세요.
//
// 설명: (디자인 패턴을 통해 어떤 부분이 개선이 되었는지)
// ════════════════════════════════════════════════════════════════


// ── main (수정하지 마세요) ───────────────────────────────────
int main() {
    // BAD: 공격 방식이 클래스에 하드코딩, 런타임 변경 불가
    BadKnight bk("Arthur"); bk.attack();
    BadWizard bw("Merlin"); bw.attack();
    BadArcher ba("Robin");  ba.attack();

    // GOOD: 전략을 외부에서 주입, 런타임 교체 가능
    Knight knight("Arthur");
    Wizard wizard("Merlin");
    Archer archer("Robin");
    knight.attack();
    wizard.attack();
    archer.attack();

    knight.setAttackStrategy(new MagicAttack());
    knight.attack();

    knight.setAttackStrategy(new BowAttack());
    knight.attack();

    return 0;
}
// ─────────────────────────────────────────────────────────────
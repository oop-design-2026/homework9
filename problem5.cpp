/*
 * Problem 5: Decorator Pattern
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
class BadKnight {
protected:
    string name;
    int baseAttack;
public:
    BadKnight(const string& n, int a) : name(n), baseAttack(a) {}
    virtual ~BadKnight() = default;
    virtual void showStats() const {
        cout << "Knight " << name << " | Attack: " << baseAttack << "\n";
    }
};
class BadKnightWithSword : public BadKnight {
public:
    BadKnightWithSword(const string& n, int a) : BadKnight(n, a) {}
    void showStats() const override {
        cout << "Knight " << name << " | Attack: " << baseAttack + 10 << " [Sword 장착]" << "\n";
    }
};
class BadKnightWithMagicRing : public BadKnight {
public:
    BadKnightWithMagicRing(const string& n, int a) : BadKnight(n, a) {}
    void showStats() const override {
        cout << "Knight " << name << " | Attack: " << baseAttack + 20 << " [MagicRing 장착]" << "\n";
    }
};
class BadKnightWithSwordAndMagicRing : public BadKnight {
public:
    BadKnightWithSwordAndMagicRing(const string& n, int a) : BadKnight(n, a) {}
    void showStats() const override {
        cout << "Knight " << name << " | Attack: " << baseAttack + 30
             << " [Sword 장착, MagicRing 장착]" << "\n";
    }
};
// Wizard, Archer 에도 같은 조합이 필요하다면? → class 폭발

// ════════════════════════════════════════════════════════════════
// [GOOD] 여기서부터 구현하세요
// main() 을 보고 Decorator Pattern 을 직접 설계하세요.
//   - 모든 캐릭터와 Decorator 가 공유하는 인터페이스를 만드세요.
//   - Decorator 는 그 인터페이스의 포인터를 내부에 보유하고 감싸세요.
//   - getLabel() 을 재귀적으로 연결하여 장비 목록을 누적 출력하세요.
//
// 설명: (디자인 패턴을 통해 어떤 부분이 개선이 되었는지)
// ════════════════════════════════════════════════════════════════


// ── main (수정하지 마세요) ───────────────────────────────────
int main() {
    // BAD: 조합마다 별도 class 필요 → class 폭발
    BadKnight("Arthur", 50).showStats();
    BadKnightWithSword("Arthur", 50).showStats();
    BadKnightWithMagicRing("Arthur", 50).showStats();
    BadKnightWithSwordAndMagicRing("Arthur", 50).showStats();

    // GOOD: 같은 Decorator 를 어떤 캐릭터에도 자유롭게 조합
    Character* k = new Knight("Arthur", 50);
    k->showStats();
    k = new Sword(k);
    k->showStats();
    k = new MagicRing(k);
    k->showStats();
    k = new PowerBoost(k);
    k->showStats();
    delete k;

    Character* w = new PowerBoost(new MagicRing(new Wizard("Merlin", 40)));
    w->showStats();
    delete w;

    Character* a = new PowerBoost(new Sword(new Archer("Robin", 35)));
    a->showStats();
    delete a;

    return 0;
}

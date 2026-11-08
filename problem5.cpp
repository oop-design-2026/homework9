/*
 * Problem 5: Decorator Pattern
 * 학번:
 * 이름:
 *
 * 컴파일: g++ -std=c++17 -o problem5 problem5.cpp
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
//
// main() 을 보고 Decorator Pattern 을 직접 설계하세요.
//   - 모든 캐릭터와 Decorator 가 공유하는 인터페이스를 만드세요.
//   - Decorator 는 그 인터페이스의 포인터를 내부에 보유하고 감싸세요.
//   - getLabel() 을 재귀적으로 연결하여 장비 목록을 누적 출력하세요.
// ════════════════════════════════════════════════════════════════

// ════════════════════════════════════════════════════════════════
// main (수정하지 마세요)
// ════════════════════════════════════════════════════════════════
int main() {
    cout << "=== [BAD] Decorator 적용 전: 조합마다 별도 class 필요 ===" << "\n";
    BadKnight("Arthur", 50).showStats();                       // "Knight Arthur | Attack: 50"
    BadKnightWithSword("Arthur", 50).showStats();              // "Knight Arthur | Attack: 60 [Sword 장착]"
    BadKnightWithMagicRing("Arthur", 50).showStats();          // "Knight Arthur | Attack: 70 [MagicRing 장착]"
    BadKnightWithSwordAndMagicRing("Arthur", 50).showStats();  // "Knight Arthur | Attack: 80 [Sword 장착, MagicRing 장착]"
    cout << "[문제] PowerBoost 추가 시 BadKnightWithSwordAndMagicRingAndPowerBoost 필요" << "\n";
    cout << "[문제] Wizard, Archer 도 같은 조합 필요 → class 폭발" << "\n";

    cout << "\n=== [GOOD] Decorator 적용 후: 자유롭게 조합 ===" << "\n";
    Character* k = new Knight("Arthur", 50);
    k->showStats();              // "Knight Arthur | Attack: 50"
    k = new Sword(k);
    k->showStats();              // "Knight Arthur | Attack: 60 [+Sword(10)]"
    k = new MagicRing(k);
    k->showStats();              // "Knight Arthur | Attack: 80 [+Sword(10)] [+MagicRing(20)]"
    k = new PowerBoost(k);
    k->showStats();              // "Knight Arthur | Attack: 95 [+Sword(10)] [+MagicRing(20)] [+PowerBoost(15)]"
    delete k;

    cout << "\n[Wizard 도 같은 Decorator 재사용]" << "\n";
    Character* w = new PowerBoost(new MagicRing(new Wizard("Merlin", 40)));
    w->showStats();              // "Wizard Merlin | Attack: 75 [+MagicRing(20)] [+PowerBoost(15)]"
    delete w;

    cout << "\n[Archer 에 Sword + PowerBoost 조합]" << "\n";
    Character* a = new PowerBoost(new Sword(new Archer("Robin", 35)));
    a->showStats();              // "Archer Robin | Attack: 60 [+Sword(10)] [+PowerBoost(15)]"
    delete a;

    cout << "\n[확인] Character class 수정 없이 새 장비 추가 및 자유롭게 중첩 가능" << "\n";
    return 0;
}

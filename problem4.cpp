/*
 * Problem 4: Strategy Pattern
 * 학번:
 * 이름:
 *
 * 컴파일: g++ -std=c++17 -o problem4 problem4.cpp
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
//
// main() 을 보고 Strategy Pattern 을 직접 설계하세요.
//   - 공격 행동을 캡슐화하는 인터페이스를 만드세요.
//   - 캐릭터가 그 인터페이스의 포인터를 HAS-A 로 보유하게 하세요.
//   - setAttackStrategy() 로 런타임에 교체 가능하게 하세요.
// ════════════════════════════════════════════════════════════════

// ════════════════════════════════════════════════════════════════
// main (수정하지 마세요)
// ════════════════════════════════════════════════════════════════
int main() {
    cout << "=== [BAD] Strategy Pattern 적용 전 ===" << "\n";
    BadKnight bk("Arthur"); bk.attack();   // "Arthur swings a Sword!"
    BadWizard bw("Merlin"); bw.attack();   // "Merlin casts a Magic spell!"
    BadArcher ba("Robin");  ba.attack();   // "Robin shoots a Bow!"
    cout << "[문제] 공격 방식을 런타임에 변경할 수 없음" << "\n";
    cout << "[문제] 새 공격 추가 시 BadCharacter::attack() 수정 필요" << "\n";

    cout << "\n=== [GOOD] Strategy Pattern 적용 후 ===" << "\n";
    Knight knight("Arthur");
    Wizard wizard("Merlin");
    Archer archer("Robin");
    cout << "[" << knight.getRole() << "] "; knight.attack();  // "[Knight] Arthur swings a Sword!"
    cout << "[" << wizard.getRole() << "] "; wizard.attack();  // "[Wizard] Merlin casts a Magic spell!"
    cout << "[" << archer.getRole() << "] "; archer.attack();  // "[Archer] Robin shoots a Bow!"

    cout << "\n[런타임 행동 변경] Knight Arthur → MagicAttack 장착" << "\n";
    knight.setAttackStrategy(new MagicAttack());
    cout << "[" << knight.getRole() << "] "; knight.attack();  // "[Knight] Arthur casts a Magic spell!"

    cout << "\n[런타임 행동 변경] Knight Arthur → BowAttack 장착" << "\n";
    knight.setAttackStrategy(new BowAttack());
    cout << "[" << knight.getRole() << "] "; knight.attack();  // "[Knight] Arthur shoots a Bow!"

    cout << "\n[확인] Character class 수정 없이 새 공격 방식 추가 및 런타임 변경 가능" << "\n";
    return 0;
}

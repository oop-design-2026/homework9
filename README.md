## 개요

C++의 Downcasting, RTTI, Type Confusion, 그리고 디자인 패턴(Strategy / Decorator)을 실습합니다.  
총 5문제로 구성되어 있으며, 각 `problem*.cpp` 파일에 클래스와 함수를 구현하세요.  
`main.cpp` 는 수정하지 않습니다.

- **Problem 1 ~ 3**: `main.cpp` + `problem1~3.cpp` 를 함께 컴파일하여 자동 채점됩니다.
- **Problem 4 ~ 5**: 각 파일을 단독으로 컴파일하며, 직접 채점합니다.

---

## 개발 환경 준비

g++ 컴파일러가 필요합니다. 이미 설치되어 있다면 다음 단계로 넘어가세요.

| 운영체제 | 설치 방법 |
|---|---|
| Windows | [MSYS2](https://www.msys2.org/) 설치 후 `pacman -S mingw-w64-ucrt-x86_64-gcc` |
| macOS | 터미널에서 `xcode-select --install` |
| Linux (Ubuntu) | `sudo apt install build-essential` |

설치 확인:
```bash
g++ --version
```

---

## 파일 구조

```
homework9/
├── main.cpp              ← 수정 금지. Problem 1~3 테스트 실행 로직.
├── problem1.cpp          ← Problem 1 구현 (Downcasting)
├── problem2.cpp          ← Problem 2 구현 (RTTI & dynamic_cast)
├── problem3.cpp          ← Problem 3 구현 (Type Confusion)
├── problem4.cpp          ← Problem 4 구현 (Strategy Pattern) — 단독 컴파일
├── problem5.cpp          ← Problem 5 구현 (Decorator Pattern) — 단독 컴파일
├── test9.sh              ← 채점 스크립트 (macOS / Linux)
├── test9.bat             ← 채점 스크립트 (Windows)
└── Test/
    ├── case1.txt         ← 테스트 케이스 1 입력 데이터
    ├── case2.txt         ← 테스트 케이스 2 입력 데이터
    ├── case3.txt         ← 테스트 케이스 3 입력 데이터
    ├── expected1.txt     ← 테스트 케이스 1 기대 출력
    ├── expected2.txt     ← 테스트 케이스 2 기대 출력
    └── expected3.txt     ← 테스트 케이스 3 기대 출력
```

---

## 문제 1 — Downcasting (`problem1.cpp`)

`Character` 클래스는 이미 제공되어 있습니다.  
`Knight`, `Wizard` 클래스와 `performCasting`, `showWrongCasting` 함수를 구현하세요.

**활용 개념**

- Base Class Pointer 로 Derived Object 를 참조하는 Upcasting
- `static_cast` 를 이용한 Downcasting
- Derived Class 에서만 제공하는 고유 메서드 호출
- 잘못된 타입으로의 Downcasting 이 Undefined Behavior 를 유발함을 확인

**구현할 클래스 및 함수**

| 클래스 / 함수 | 설명 |
|---|---|
| `Knight` | `swordLevel` (int) 추가 멤버, `describe()`, `knightCharge(int times)` |
| `Wizard` | `manaPool` (int) 추가 멤버, `describe()`, `castUltimate()` |
| `performCasting` | `static_cast` 로 올바르게 Downcast 하여 고유 메서드 호출 |
| `showWrongCasting` | Knight 를 Wizard* 로 잘못 변환 시 static_cast / dynamic_cast 동작 비교 |

**기대 출력 — Arthur(HP:100, SwordLv:3, charge:2), Merlin(HP:80, Mana:150) 기준**

```
=== Problem 1: Downcasting ===
[Part 1] Upcasting: Base Class Pointer
Knight Arthur (HP:100, SwordLv:3)
Wizard Merlin (HP:80, Mana:150)
[Part 2] Correct Downcasting (static_cast)
Knight Arthur charges 2 times with sword (Lv.3)!
Wizard Merlin unleashes a spell consuming 150 mana!
[Part 3] Wrong Downcasting: Undefined Behavior Risk
[Wrong] static_cast<Wizard*>(p1) returned non-null — static_cast has no type check!
[!!] Calling wrong->castUltimate() would be Undefined Behavior!
[Safe] dynamic_cast<Wizard*>(p1) returned nullptr
```

---

## 문제 2 — RTTI & dynamic_cast (`problem2.cpp`)

`Character`, `Knight`, `Wizard` 클래스는 이미 제공되어 있습니다.  
`identifyAndCast`, `safeRefCast` 함수를 직접 구현하세요.

**활용 개념**

- `typeid` 와 `type_info::operator==` 를 이용한 런타임 타입 식별 (RTTI)
- `dynamic_cast` (포인터): 실패 시 `nullptr` 반환
- `dynamic_cast` (레퍼런스): 실패 시 `std::bad_cast` 예외 발생

**구현할 함수**

| 함수 | 설명 |
|---|---|
| `identifyAndCast(Character* c)` | `typeid` 로 타입 출력 후 `dynamic_cast` (포인터) 로 고유 메서드 호출 |
| `safeRefCast(Character& c)` | `dynamic_cast` (레퍼런스) 시도, 실패 시 `bad_cast` 처리 |

**기대 출력 — Arthur(HP:100, SwordLv:3), Merlin(HP:80, Mana:150) 기준**

```
=== Problem 2: RTTI & dynamic_cast ===
[Part 1] typeid + dynamic_cast (pointer)
--- party[0] ---
[typeid] Type: Knight
[dynamic_cast] Knight*: SUCCESS
Knight Arthur challenges you to a duel!
[dynamic_cast] Wizard*: FAILED (nullptr)
--- party[1] ---
[typeid] Type: Wizard
[dynamic_cast] Knight*: FAILED (nullptr)
[dynamic_cast] Wizard*: SUCCESS
Wizard Merlin reveals the secrets of the arcane!
[Part 2] dynamic_cast (reference) + bad_cast
--- party[0] ---
[ref cast] Knight&: SUCCESS
Knight Arthur challenges you to a duel!
[ref cast] Wizard&: bad_cast caught
--- party[1] ---
[ref cast] Knight&: bad_cast caught
[ref cast] Wizard&: SUCCESS
Wizard Merlin reveals the secrets of the arcane!
```

---

## 문제 3 — Type Confusion (`problem3.cpp`)

`Entity` 클래스는 이미 제공되어 있습니다.  
`Warrior`, `Mage` 클래스와 `analyzeConfusion`, `safeDispatch` 함수를 구현하세요.

**활용 개념**

- Type Confusion: `static_cast` 는 타입을 검사하지 않아 항상 non-null 반환 → Undefined Behavior 위험
- `dynamic_cast` 는 런타임 타입을 검사하여 실패 시 `nullptr` 반환
- `dynamic_cast` 를 이용한 안전한 분기 처리 (Safe Dispatch)

**구현할 클래스 및 함수**

| 클래스 / 함수 | 설명 |
|---|---|
| `Warrior` | `getType()` → `"Warrior"`, `slash()` 출력 |
| `Mage` | `getType()` → `"Mage"`, `chant()` 출력 |
| `analyzeConfusion(Entity* e)` | static_cast / dynamic_cast 를 모두 시도하여 동작 차이 출력 |
| `safeDispatch(Entity* e)` | `dynamic_cast` 로 실제 타입 확인 후 적절한 메서드 호출 |

**기대 출력 — Tristan(power:25), Morgana(mana:180) 기준**

```
=== Problem 3: Type Confusion ===
[Part 1] analyzeConfusion: static_cast vs dynamic_cast
--- p1 (Warrior) ---
[static_cast] Warrior*: non-null (type not checked)
[static_cast] Mage*: non-null (type not checked)
[dynamic_cast] Warrior*: SUCCESS
[dynamic_cast] Mage*: nullptr
--- p2 (Mage) ---
[static_cast] Warrior*: non-null (type not checked)
[static_cast] Mage*: non-null (type not checked)
[dynamic_cast] Warrior*: nullptr
[dynamic_cast] Mage*: SUCCESS
[Part 2] safeDispatch: dynamic_cast in action
Warrior Tristan slashes the enemy for 25 damage!
Mage Morgana chants a spell with 180 mana!
```

---

## 문제 4 — Strategy Pattern (`problem4.cpp`)

BAD 코드의 문제점을 파악한 뒤, `main()` 의 호출 방식을 보고 Strategy Pattern 을 직접 설계하세요.  
`AttackStrategy` 인터페이스부터 `Knight`, `Wizard`, `Archer` 까지 모두 직접 구현합니다.

**컴파일 및 실행**

```bash
g++ -std=c++17 -o problem4 problem4.cpp
./problem4
```

**BAD 코드의 문제점**

- 공격 방식 추가 시 `BadCharacter::attack()` 을 직접 수정해야 함 (OCP 위반)
- 런타임에 공격 방식을 변경할 수 없음

**Strategy Pattern 의 핵심**

- 공격 행동을 인터페이스로 분리하여 캡슐화
- 캐릭터가 전략 객체를 HAS-A 로 보유
- `setAttackStrategy()` 로 런타임에 행동 교체 가능

---

## 문제 5 — Decorator Pattern (`problem5.cpp`)

BAD 코드의 문제점을 파악한 뒤, `main()` 의 호출 방식을 보고 Decorator Pattern 을 직접 설계하세요.  
`Character` 인터페이스부터 `Knight`, `Wizard`, `Archer`, 그리고 `Sword`, `MagicRing`, `PowerBoost` Decorator 까지 모두 직접 구현합니다.

**컴파일 및 실행**

```bash
g++ -std=c++17 -o problem5 problem5.cpp
./problem5
```

**BAD 코드의 문제점**

- 장비 조합마다 별도 class 필요 (n개 장비 → 최대 2ⁿ 조합)
- Wizard, Archer 에도 동일한 조합 class 가 모두 필요 → class 폭발

**Decorator Pattern 의 핵심**

- 모든 캐릭터와 Decorator 가 공통 인터페이스를 구현
- Decorator 는 `Character*` 를 내부에 보유하고 기능을 위임 + 추가
- `getLabel()` 을 재귀적으로 연결하여 장비 목록을 누적 출력

---

## 테스트 방법 (Problem 1 ~ 3 자동 채점)

```bash
# macOS / Linux
bash test9.sh

# Windows
test9.bat
```

테스트 케이스 3개를 순서대로 실행하며 각 문제별로 `PASS` / `FAIL` 을 출력합니다.  
`FAIL` 인 경우 기대 출력과 실제 출력의 차이를 함께 확인하세요.

---

## 제출 방법 (git)

```bash
git add problem1.cpp problem2.cpp problem3.cpp problem4.cpp problem5.cpp
git commit -m "학번 이름"
git push
```

- push 후 저장소의 **Actions 탭** 에서 Problem 1~3 자동 채점 결과를 확인할 수 있습니다.
- Problem 4~5 는 직접 채점합니다.
- 마감 전까지 몇 번이든 다시 제출할 수 있습니다.

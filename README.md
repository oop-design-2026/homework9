## 개요

C++의 Downcasting, RTTI, Type Confusion 을 실습합니다.  
총 3문제로 구성되어 있으며, 각 `problem*.cpp` 파일에 있는 클래스와 함수를 구현하세요.  
`main.cpp` 는 수정하지 않습니다.

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
├── main.cpp              ← 수정 금지. 테스트 실행 로직.
├── problem1.cpp          ← Problem 1 구현 (Downcasting)
├── problem2.cpp          ← Problem 2 구현 (RTTI & dynamic_cast)
├── problem3.cpp          ← Problem 3 구현 (Type Confusion)
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

`Character` Base Class 를 상속받는 `Knight` 와 `Wizard` 를 구현하세요.  
`Character` 클래스는 이미 제공되어 있습니다.

**활용 개념**

- Base Class Pointer 로 Derived Object 를 참조하는 Upcasting
- `static_cast` 를 이용한 Downcasting
- Derived Class 에서만 제공하는 고유 메서드 호출
- 잘못된 타입으로의 Downcasting 이 Undefined Behavior 를 유발함을 확인

**구현할 클래스**

| 클래스 | 추가 멤버 | `describe()` 출력 | `getType()` | 고유 메서드 출력 |
|---|---|---|---|---|
| `Knight` | `swordLevel` (int) | `Knight <name> (HP:<hp>, SwordLv:<swordLevel>)` | `"Knight"` | `Knight <name> charges <times> times with sword (Lv.<swordLevel>)!` |
| `Wizard` | `manaPool` (int) | `Wizard <name> (HP:<hp>, Mana:<manaPool>)` | `"Wizard"` | `Wizard <name> unleashes a spell consuming <manaPool> mana!` |

**기대 출력 — Arthur(HP:100, SwordLv:3), Merlin(HP:80, Mana:150), chargeCount=2 기준**

```
=== Problem 1: Downcasting ===
[Part 1] Upcasting: Base Class Pointer
Knight Arthur (HP:100, SwordLv:3)
Wizard Merlin (HP:80, Mana:150)
[Part 2] Correct Downcasting (static_cast)
Knight Arthur charges 2 times with sword (Lv.3)!
Wizard Merlin unleashes a spell consuming 150 mana!
[Part 3] Incorrect Downcasting: Undefined Behavior Risk
[Check] p1 actually points to a Knight object.
[Warning] static_cast<Wizard*>(p1) would cause Undefined Behavior!
[Safe] dynamic_cast<Wizard*>(p1) = nullptr. Cast correctly rejected.
```

---

## 문제 2 — RTTI & dynamic_cast (`problem2.cpp`)

`Character` Base Class 를 상속받는 `Knight` 와 `Wizard` 를 구현하세요.

**활용 개념**

- `typeid` 와 `type_info` 를 이용한 런타임 타입 식별 (RTTI)
- `dynamic_cast` (포인터): 실패 시 `nullptr` 반환
- `dynamic_cast` (레퍼런스): 실패 시 `std::bad_cast` 예외 발생
- `static_cast` 와 `dynamic_cast` 의 안전성 차이

**구현할 클래스**

| 클래스 | 추가 멤버 | `describe()` 출력 | `getType()` | 고유 메서드 출력 |
|---|---|---|---|---|
| `Knight` | `swordLevel` (int) | `Knight <name> (HP:<hp>, SwordLv:<swordLevel>)` | `"Knight"` | `Knight <name> challenges you to a duel!` |
| `Wizard` | `manaPool` (int) | `Wizard <name> (HP:<hp>, Mana:<manaPool>)` | `"Wizard"` | `Wizard <name> reveals the secrets of the arcane!` |

**기대 출력 — Arthur(HP:100, SwordLv:3), Merlin(HP:80, Mana:150) 기준**

```
=== Problem 2: RTTI & dynamic_cast ===
[Part 1] typeid: Runtime Type Identification
party[0] runtime type: Knight
party[1] runtime type: Wizard
[Part 2] dynamic_cast (pointer): Safe Downcasting
Casting party[0] to Knight*: SUCCESS
Knight Arthur challenges you to a duel!
Casting party[0] to Wizard*: FAILED (nullptr) -- safe, no UB
Casting party[1] to Wizard*: SUCCESS
Wizard Merlin reveals the secrets of the arcane!
Casting party[1] to Knight*: FAILED (nullptr) -- safe, no UB
[Part 3] dynamic_cast (reference): std::bad_cast
Casting (Knight ref) to Knight&: SUCCESS
Knight Arthur challenges you to a duel!
Casting (Wizard ref) to Knight&: bad_cast caught!
```

---

## 문제 3 — Type Confusion (`problem3.cpp`)

`Entity` Base Class 를 상속받는 `Warrior`, `Mage` 와 `safeDispatch` 함수를 구현하세요.  
`Entity` 클래스는 이미 제공되어 있습니다.

**활용 개념**

- Type Confusion: 잘못된 Downcasting 으로 객체를 다른 타입으로 해석하는 문제
- `static_cast` 의 위험성: 런타임 타입 검사 없이 변환 → Undefined Behavior
- `dynamic_cast` 를 이용한 안전한 타입 검증 (Safe Casting)
- `std::bad_cast` 예외 처리

**구현할 클래스 및 함수**

| 클래스 / 함수 | `getType()` | 고유 메서드 출력 |
|---|---|---|
| `Warrior` | `"Warrior"` | `Warrior <name> slashes the enemy for <power> damage!` |
| `Mage` | `"Mage"` | `Mage <name> chants a spell with <power> mana!` |
| `safeDispatch(Entity*)` | — | `dynamic_cast` 로 타입 확인 후 `slash()` 또는 `chant()` 호출 |

**기대 출력 — Tristan(power:25), Morgana(power:180) 기준**

```
=== Problem 3: Type Confusion ===
[Part 1] Safe Dispatch: dynamic_cast in action
Warrior Tristan slashes the enemy for 25 damage!
Mage Morgana chants a spell with 180 mana!
[Part 2] Type Confusion Analysis
[Actual type] p1 is Warrior, p2 is Mage
[Danger] static_cast<Mage*>(p1) skips type check -> Undefined Behavior!
[Safe fix] dynamic_cast<Mage*>(p1) = nullptr -> cast rejected correctly
[Part 3] Reference Casting with bad_cast
Casting Entity& (Warrior) to Warrior&: SUCCESS
Warrior Tristan slashes the enemy for 25 damage!
Casting Entity& (Mage) to Warrior&: std::bad_cast caught!
Cannot treat Mage as Warrior. Type confusion prevented.
```

---

## 테스트 방법

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
git add problem1.cpp problem2.cpp problem3.cpp
git commit -m "학번 이름"
git push
```

- push 후 저장소의 **Actions 탭** 에서 자동 채점 결과를 확인할 수 있습니다.
- 마감 전까지 몇 번이든 다시 제출할 수 있습니다.

## Pattern Oriented Software Design 2026 Spring Midterm

**!! Attention !!**
- All other resources, including GitHub Copilot, ChatGPT, Stack Overflow, other websites, etc., are **forbidden**.
- You must turn off your mobile phone during the midterm exam, or you will be considered as cheating.

- **Violation of the rules will be calculated as 0 POINTS.**
- If you have any problems, please raise your hand and let TA know.

## Table of Contents
- [Midterm Template](#midterm-template)
- [Problem Statement](#problem-statement)
    - [Specification 1: Characters — `Warrior`, `Mage`, `Cleric` (20%)](#1-characters--warrior-mage-cleric-20)
    - [Specification 2: Strategy Pattern — `CombatStrategy` (20%)](#2-strategy-pattern--combatstrategy-20)
    - [Specification 3: Composite Pattern — `Party` (20%)](#3-composite-pattern--party-20)
    - [Specification 4: Iterator Pattern — `Iterator`, `NullIterator`, `PartyIterator` (20%)](#4-iterator-pattern--iterator-nulliterator-partyiterator-20)
    - [Specification 5: Visitor Pattern — `CharacterVisitor`, `BuffVisitor` (20%)](#5-visitor-pattern--charactervisitor-buffvisitor-20)
- [Build Instructions](#build-instructions)
- [Final Remarks](#final-remarks)

## Midterm Template
To start the midterm, you need to follow the steps below:
1. **Clone** your homework repository.
2. Clean the `src/`, `tests/`, and `CMakeLists.txt` in your homework repository.
3. **Download** the template code from this repository.
4. Copy the `src/`, `tests/`, and `CMakeLists.txt` from [the template code](./template_code) to your homework repository.

**Note: Each class in the template file is the skeleton. You should finish implementation by yourself.**

## Problem Statement
For this midterm, you'll build a hero combat system(英雄戰鬥系統) that uses **Composite**, **Iterator**, **Visitor**, and **Strategy** patterns.

A combat system is needed to manage heroes such as warriors(戰士), mages(法師), and clerics(牧師). Each hero has a combat style that determines how they attack. Heroes can be grouped into **parties** that are treated as a single unit, and the system must support traversing all members and performing operations on them without modifying the character classes.

### Specification
Please complete the given code to satisfy all the following conditions.

#### 1. Characters — `Warrior`, `Mage`, `Cleric` (20%)

All characters inherit from `Character`. Each character has two attributes that determine their combat capabilities, and each has a default `CombatStrategy`.

* `Character` is an abstract class with the following interface:
	* `Character(CombatStrategy*)` — constructor that takes a combat strategy.
	* `power()` — pure virtual, returns the character's overall combat strength.
	* `speed()` — pure virtual, returns the character's speed.
	* `toString()` — pure virtual, returns a string representation of the character.

* **`Warrior(atk, def)`** — A melee fighter whose strength comes from both attack and defense.
	* `atk`: attack power (physical attack strength).
	* `def`: defense power (ability to withstand hits).
	* `power() = atk * def` — overall combat strength from combining offense and defense.
	* `speed() = atk + def` — the higher the physical stats, the faster the warrior moves.
	* Default strategy: `MeleeStrategy`.

* **`Mage(intelligence, mp)`** — A spell caster whose power scales with intellect and mana.
	* `intelligence`: intellect (determines spell potency).
	* `mp`: mana points (resource pool for casting spells).
	* `power() = intelligence * mp` — spell damage depends on both intellect and available mana.
	* `speed() = intelligence * 2` — a mage's reaction time depends on brainpower, not mana.
	* Default strategy: `MagicStrategy`.

* **`Cleric(faith, hp)`** — A healer/support whose divine power comes from faith and vitality.
	* `faith`: faith value (source of holy power).
	* `hp`: hit points (the cleric's own life force).
	* `power() = faith * hp * 0.5` — halved because clerics focus on support, not raw damage.
	* `speed() = faith + hp` — deeper faith and stronger life force means faster action.
	* Default strategy: `HealStrategy`.

* `toString()` format examples: `"Warrior (10 5)"`, `"Mage (8.5 12)"`, `"Cleric (6 10)"`.
* Each character class must expose attribute getters/setters (e.g., `atk()` / `setAtk()`, `intelligence()` / `setIntelligence()`, `faith()` / `setFaith()`).
* Please do exception handling if the character can't be successfully created. (The exception type of the TA's test will be `std::string` and throw `It's not a warrior!`, `It's not a mage!`, `It's not a cleric!`.)

#### 2. Strategy Pattern — `CombatStrategy` (20%)

Each character has a default combat style, but the damage formula should not be hardcoded in the character class. Instead, damage calculation is encapsulated in a `CombatStrategy` object, so that a character's combat behavior can be switched at runtime via `setCombatStyle()` — for example, a `Warrior` could switch from `MeleeStrategy` to `MagicStrategy` without modifying the `Warrior` class. There are three strategies: `MeleeStrategy`(近戰) for physical melee attacks, `MagicStrategy`(魔法) for spell-based attacks that ignore defense, and `HealStrategy`(治療) for healing (negative damage).

* `CombatStrategy` is an abstract class with the following interface:
	* `damage(powerOfCharacter, targetDefense)` — calculates and returns the damage value.
	* `name()` — returns the name of the strategy.

* Implement three concrete strategies — `MeleeStrategy`, `MagicStrategy`, `HealStrategy`:
	* `MeleeStrategy`: `damage = max(0, powerOfCharacter * 1.2 - targetDefense)`, `name() = "Melee"`
	* `MagicStrategy`: `damage = powerOfCharacter * 2.0` (ignores the target defense), `name() = "Magic"`
	* `HealStrategy`: `damage = powerOfCharacter * -0.8` (negative damage = healing), `name() = "Heal"`

* Default strategies: `Warrior` uses `MeleeStrategy`, `Mage` uses `MagicStrategy`, `Cleric` uses `HealStrategy`.

* The following methods are defined in `Character` and inherited by all subclasses:
	* `setCombatStyle(CombatStrategy*)` — switches the character's combat strategy at runtime. Any character (including `Party`) can switch strategies.
	* `combatStyleName()` — returns the name of the current combat strategy.
	* `attack(targetDef)` — calculates and returns the damage value against a target with the given defense value. It delegates to the current `CombatStrategy`'s `damage()`, passing the character's `power()` as `powerOfCharacter` and `targetDef` as `targetDefense`. This method only returns the result — it does not modify the attacker or the target.

#### 3. Composite Pattern — `Party` (20%)

Heroes can be grouped into a `Party`(隊伍) that is treated uniformly as a `Character`. This means a `Party` has its own `power()`, `speed()`, and can even contain other parties — forming a tree structure. The caller does not need to distinguish between a single character and a group of characters.

* Implement `Party` as a subclass of `Character`.
	* `Party(CombatStrategy*)` — takes a combat strategy just like any other character.
	* `add(Character*)` — adds a character or sub-party to this party.
	* `power()` — returns the **sum** of `power()` across all children. Returns `0` if empty.
	* `speed()` — returns the **minimum** `speed()` across all children. Returns `0` if empty.
	* `toString()` — format: `"Party(Warrior (10 5) Mage (8 12))"` (children separated by a single space).
	* `attack(targetDef)` — uses the party's total `power()` with its own `CombatStrategy`.
	* Nested parties are supported: a `Party` may contain other `Party` objects.

* Calling `add()` on `Warrior`, `Mage`, or `Cleric` should throw `std::string("Cannot add to a leaf character!")`.

* Example of nested `toString()`:
	```
	Party(Party(Warrior (3 4) Mage (5 6)) Cleric (2 10))
	```

#### 4. Iterator Pattern — `Iterator`, `NullIterator`, `PartyIterator` (20%)

A `Party` owns a collection of children, but its internal data structure (e.g., `std::vector`) should not be exposed publicly. The Iterator pattern provides a way to traverse the direct children of a `Party` without revealing how they are stored. Leaf characters (`Warrior`, `Mage`, `Cleric`) have no children, so they return a `NullIterator` that does nothing.

* Implement abstract `Iterator` with:
	* `first()` — reset to the beginning.
	* `next()` — advance to the next element.
	* `isDone()` — returns `true` if traversal is complete.
	* `currentItem()` — returns the current `Character*` (or `nullptr` if done).

* Implement `NullIterator`:
	* All methods do nothing; `isDone()` always returns `true`; `currentItem()` returns `nullptr`.
	* Used as the default iterator for leaf characters (`Warrior`, `Mage`, `Cleric`).

* Implement `PartyIterator`:
	* Traverses **only the direct children** of a `Party` (does **not** recurse into sub-parties).
	* Example: for `Party(Warrior(10 5), Party(Mage(8 12), Cleric(6 10)))`, the iterator yields `Warrior(10 5)` then the inner `Party` itself, then `isDone()`.
	* `PartyIterator` should be declared as a `friend` of `Party` so it can access the children directly without exposing them publicly. **`Party` must NOT expose `getChildren()`** — the only way to traverse a party is through its iterator.

* `Character` should provide:
	* `createIterator()` — returns a `NullIterator` by default.
	* `Party` overrides `createIterator()` to return a `PartyIterator`.

* `first()` must be able to reset traversal even after `isDone()` is true.
* Calling `currentItem()` when `isDone()` is true should return `nullptr`.

#### 5. Visitor Pattern — `CharacterVisitor`, `BuffVisitor` (20%)

Sometimes we want to perform operations on characters (e.g., applying buffs) without modifying the character classes themselves. The Visitor pattern separates the operation from the object structure — new operations can be added by creating a new visitor, without changing `Warrior`, `Mage`, or `Cleric`. Here you will implement a `BuffVisitor` that permanently boosts a character's attribute by a multiplicative factor on each visit.

* Add `accept(CharacterVisitor*)` as a pure virtual method in `Character`.

* Implement abstract `CharacterVisitor` with:
	* `visitWarrior(Warrior*)`
	* `visitMage(Mage*)`
	* `visitCleric(Cleric*)`
	* `visitParty(Party*)`

* Implement `BuffVisitor`:
	* Applies a one-time multiplicative buff per visit:
		* `Warrior`: `atk *= 1.5`
		* `Mage`: `intelligence *= 1.3`
		* `Cleric`: `faith *= 1.2`
	* Applying `BuffVisitor` twice stacks: `atk *= 1.5 * 1.5`.
	* `visitParty()` must traverse the party's direct children using `createIterator()` and call `accept(this)` on each child. Sub-parties will recurse naturally through `accept()`.

#### General Requirements

* **For each function/method, write at least one unit test for it**.
* Please make your directory follow the following file structure:

```
├── CMakeLists.txt
├── src
│   ├── combat_strategy.h
│   ├── combat_strategy.cpp
│   ├── character.h
│   ├── character.cpp
│   ├── warrior.h
│   ├── warrior.cpp
│   ├── mage.h
│   ├── mage.cpp
│   ├── cleric.h
│   ├── cleric.cpp
│   ├── party.h
│   ├── party.cpp
│   ├── iterator.h
│   ├── null_iterator.h
│   ├── null_iterator.cpp
│   ├── party_iterator.h
│   ├── party_iterator.cpp
│   ├── character_visitor.h
│   ├── buff_visitor.h
│   └── buff_visitor.cpp
└── tests
    ├── warrior_test.cpp
    ├── mage_test.cpp
    ├── cleric_test.cpp
    ├── party_test.cpp
    ├── iterator_test.cpp
    └── visitor_test.cpp
```

### Build Instructions
```bash
mkdir build
cd build
cmake ..
make
```

- Execute unit tests: `./unit_tests`

## Final Remarks
Congratulations! You have finished the midterm exam. Please check the following things before you leave:
- The code is committed and pushed to your remote repository.
- The status of Jenkins is passed.
- All tests pass on the TA's test.
- Make sure you follow the instructions and requirements.
- Check your code and make sure it is well-formatted and readable.
- Clean unused code and remove unnecessary comments.

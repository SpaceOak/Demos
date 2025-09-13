# Gameplay Action System (Demo)

This project demonstrates a **gameplay action architecture**, built on top of an object manager and slot-based container.  
The goal is to show how game objects (Entities) can own and manage actions through a unified interface.

---

## 📐 UML Diagram

![UML Diagram](//www.plantuml.com/plantuml/dpng/XLJDRXCn4BxxAKOzb4qWhNgjegW1fO14gO305JdUITRKQwVsB11H3bouSaVY7Ie48X8_l8BxHdZNMxBPH739UhwP-RvlPpqvSiGj5RbY94aXtEKvpXLVmEda1GhQ7mgIHiFGYanI00gBa4mBfJgC2SMTWoVAq0cVZ-4D0xWfjKDBoRZRWKEuntMgi8JHSeT9ZClCn1XLuZEa1ZhkbjZKsEV8HPOSwmvxMyj4Fq58yndQMkmnpgGZjCbujrF6JxLj8SV6ZY9L5TxXIWsLIawGCfFUWhszlOR4I9EaHQGUfcbyzVuuFWT9nH03bmIxTNr4QcExRRQOZPmFUOvLeoChzImQqhVncNHoeZ0vFuJgA5LeV5IWNJH7DNgDeY1CMePR1gBIlnbVeY1Z-ytkxg0nwJdgYDR00oFEvbAShO7tjPi7dXfZDy1_yfTNx_nt_zL_yR_yPt_fV_hbrGUspMMlTp5eVTArEkXVz7fD9vl9bglDWas77uEl7_vt-FqMdBttIx-i-s3dO0UweQbyRZ6yKTPTBsEjwnbg_Yu6OzeGWfMpZC1CLpZK2zARS8Sf2AE9IutsC6H2E_692cquHOjQeAlGq-IW0t79zgkbOgXJA0NQCjlU0i9GChII74ojoTjVe1IutYctNsXxVGPUqKGBgni5vqKWG_SV3moglnKmbHfGnaFobMwoXZa47AM5F9fPKHw5Kv6hFm00)

---

## ⚙️ Core Components

- **Entity** – Game object that owns a set of actions  
- **EntityAction** – Base class for all actions (name, visibility, execution)  
- **EntityActionManager** – Manages registration and visibility of actions  
- **ObjectManager<T>** – Generic manager with iteration & bulk calls  
- **SlotMap<T>** – Handle-based container with stable references and O(1) insert/erase  

---

## 🛠 Example Actions

- `OpenAction` — Open an object  
- `LockpickAction` — Pick a lock  
- `InspectAction` — Inspect an object  

---

## ✅ Testing

Unit tests are implemented with **GoogleTest** in `Bohemia_Tests/EntityActionTests.cpp`.

---

## 🚀 Build & Run

```bash
git clone https://github.com/SpaceOak/Demos.git

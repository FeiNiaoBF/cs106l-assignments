/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include <cassert>
#include <iostream>
#include <vector>

#include "class.h"

void sandbox() {
  std::cout << "--- Testing Potion Class ---" << std::endl;

  // 1. 测试默认构造函数 (水瓶)
  Potion waterBottle;
  std::cout << "Default Potion (Water Bottle): " << waterBottle.getDescription()
            << std::endl;
  assert(waterBottle.getEffectType() == "Water");
  assert(waterBottle.getLevel() == 0);
  assert(waterBottle.getDurationSeconds() == 0);
  assert(waterBottle.getDosesLeft() == 1);
  assert(waterBottle.isIdentified() == true);
  assert(waterBottle.getIngredients().empty());  // 默认水瓶无成分

  waterBottle.consumeDose();
  assert(waterBottle.isEmpty() == true);
  std::cout << "Water Bottle consumed." << std::endl;

  std::cout << "\n--- Testing Custom Potions ---" << std::endl;

  // 2. 测试自定义构造函数 (力量药水 II)
  Potion strengthPotion(
      "Strength", 1, 180, 1,
      {"Nether Wart", "Blaze Powder"});  // 等级1代表II级, 180秒=3:00
  std::cout << "Strength Potion: " << strengthPotion.getDescription()
            << std::endl;
  assert(strengthPotion.getEffectType() == "Strength");
  assert(strengthPotion.getLevel() == 1);  // 等级 II
  assert(strengthPotion.getDurationSeconds() == 180);
  assert(strengthPotion.getFormattedDuration() == "3:00");
  assert(strengthPotion.getDosesLeft() == 1);
  assert(strengthPotion.isIdentified() ==
         true);  // 创建时已知效果类型，所以已鉴定
  assert(strengthPotion.getIngredients().size() == 2);

  // 3. 测试自定义构造函数 (未鉴定药水，效果是中毒)
  // 假设我们创建一个毒药水，但初始不指明类型，或者用 "Unknown"
  Potion unknownPoison("Poison", 0, 60, 2,
                       {"Spider Eye"});  // 等级0=I, 60秒, 2剂
  // 如果创建时效果已知，则构造函数会让它 identified = true
  // 要模拟未鉴定，可以在构造后手动设置，或者修改构造函数逻辑（但不建议）
  // 或者创建一个效果是"Unknown"的药水
  Potion trulyUnknown("Unknown", 0, 0, 1);  // 模拟捡到的未知药水
  std::cout << "Unknown Potion: " << trulyUnknown.getDescription() << std::endl;
  assert(trulyUnknown.isIdentified() == false);
  assert(trulyUnknown.getEffectType() == "Unknown");

  // 测试鉴定
  std::cout << "Identifying the unknown potion..." << std::endl;
  trulyUnknown.identifyPotion();  // 鉴定它 (虽然我们的实现只是简单设为true,
                                  // 效果仍是Unknown)
  // 注意：我们的默认"Unknown"药水鉴定后效果依然是"Unknown"，除非构造时给了真实效果
  // 让我们用之前的 Poison 药水演示（假设它开始时 identified 是 false）
  // Potion unknownPoison(...) -> 假设构造函数可以设置 identified = false;
  // std::cout << "Before Identify: " << unknownPoison.getDescription() <<
  // std::endl; unknownPoison.identifyPotion(); std::cout << "After Identify: "
  // << unknownPoison.getDescription() << std::endl;
  // assert(unknownPoison.getEffectType() == "Poison");

  // 4. 测试 Setters 和状态改变
  std::cout << "\n--- Testing Setters and State Changes ---" << std::endl;
  Potion speedPotion("Speed", 0, 180, 3);  // 速度 I (3:00), 3剂
  std::cout << "Initial Speed Potion: " << speedPotion.getDescription()
            << std::endl;
  speedPotion.addIngredient("Sugar");
  speedPotion.addIngredient(
      "Redstone Dust");  // 添加成分 (我们的实现不改变鉴定状态)
  std::cout << "Speed Potion after adding ingredients: "
            << speedPotion.getDescription() << std::endl;
  assert(speedPotion.getIngredients().size() == 2);

  std::cout << "Consuming speed potion doses..." << std::endl;
  int initialDoses = speedPotion.getDosesLeft();
  for (int i = 0; i < initialDoses; ++i) {
    assert(!speedPotion.isEmpty());
    speedPotion.consumeDose();
    std::cout << "Doses left: " << speedPotion.getDosesLeft() << std::endl;
  }
  assert(speedPotion.isEmpty());
  std::cout << "Speed potion is now empty." << std::endl;

  // 5. 测试瞬间效果药水
  std::cout << "\n--- Testing Instant Potions ---" << std::endl;
  Potion healingPotion("Healing", 1, 0, 1);  // 治疗 II (等级1), 持续0, 1剂
  std::cout << "Healing Potion: " << healingPotion.getDescription()
            << std::endl;
  assert(healingPotion.isInstant() == true);
  assert(healingPotion.getDurationSeconds() == 0);
  assert(healingPotion.getFormattedDuration() == "");  // 瞬间效果无格式化时间

  std::cout << "\n--- Potion Class Testing Complete ---" << std::endl;
}

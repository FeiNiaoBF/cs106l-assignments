#ifndef POTION_H
#define POTION_H

#include <set>
#include <string>
#include <vector>

class Potion {
 public:
  // --- 构造函数 ---
  // 自定义: 类型, 等级(放大器), 持续时间(秒), 剂量, 成分
  Potion(std::string type, int level, int duration, int doses,
         const std::vector<std::string>& initialIngredients = {});
  // 默认: 创建一个 "水瓶"
  Potion();

  // --- 公共 Getters (const) ---
  std::string getEffectType() const;
  int getLevel() const;            // 获取效果等级
  int getDurationSeconds() const;  // 获取持续时间
  int getDosesLeft() const;
  bool isIdentified() const;
  std::vector<std::string> getIngredients() const;
  std::string getFormattedDuration() const;  // 获取 MM:SS 格式的时间

  // --- 公共 Setters ---
  void addIngredient(const std::string& ingredient);

  // --- 其他公共方法 ---
  void consumeDose();
  bool isEmpty() const;
  void identifyPotion();
  std::string getDescription() const;  // 获取完整描述
  bool isInstant() const;              // 效果是否是瞬间的?
  void setDosesLeft(int doses);

 private:
  // --- 私有成员变量 ---
  std::string effectType;
  int effectLevel;  // 效果等级/放大器 (0=I, 1=II, etc. 或 1=I, 2=II) - 需要明确
  int durationSeconds;                   // 持续时间 (秒)
  int dosesLeft;                         // 剩余剂量
  std::vector<std::string> ingredients;  // 成分列表
  bool identified;                       // 是否已鉴定

  // --- 私有成员函数 ---
  bool isValidEffectType(const std::string& type) const;
  std::string generateDescriptionString() const;
  std::string formatSecondsToMMSS(int seconds) const;  // 辅助格式化时间

  // 存储有效的 Minecraft 风格药水效果类型
  static const std::set<std::string> validEffectTypes;
};

#endif  // POTION_H

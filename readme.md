有道词典API得到单词发音mp3
http://dict.youdao.com/dictvoice?type=0&audio=

讯飞在线语音合成
https://www.xfyun.cn/services/online_tts#anchor4503211

百度语音合成
https://ai.baidu.com/tech/speech/tts_online
## 文件结构



## enWords.db数据结构
### 表words,
- words表有两个字段，一个name是单词的英文，一个value是一个json数据 。json数据中有用的key:
    + symbols(是一个数组，内容是音标+词性+翻译) , 
    + exchange（是一个字典，内容是单词的复数，过去式，等） , 
    + memory_skill(是字符串，内容是记忆单词的技巧)

### 表user
 "CREATE TABLE user(  id INTEGER  PRIMARY KEY  AUTOINCREMENT  , dateCreate  VARCHAR(50)  NOT NULL,grade  INTEGER    NOT NULL, name   VARCHAR(50),  vip  REAL   NOT NULL)";
 - id  PRIMARY KEY
- name 用户名
- grade 年级
- dateCreate  创建时间
- vip 

### 表wangceilin
- "字段数:0     字段名:id     字段类型:INTEGER"
- "字段数:1     字段名:dateVector     字段类型:TEXT" 学习时间
- "字段数:2     字段名:errorCount     字段类型:INTEGER"  错误次数
- "字段数:3     字段名:word     字段类型:VARCHAR(50)"  单词
- "字段数:4     字段名:count     字段类型:INTEGER"  学习次数


import re

def load_sensitive_words(file_path):
    """
    读取敏感词文件，返回敏感词列表
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            # 读取所有行，去除每行末尾的换行符和首尾空格
            words = [line.strip() for line in f.readlines() if line.strip()]
        return words
    except FileNotFoundError:
        print(f"错误：找不到敏感词文件 {file_path}，请检查文件是否存在。")
        return []

def replace_sensitive_words(text, sensitive_words):
    """
    将文本中的敏感词替换为对应数量的 '*'
    使用正则替换，确保替换的是整个单词而不是部分匹配
    """
    # 对敏感词进行排序，长的排在前面，避免短词先匹配导致长词被拆分（例如先匹配了'傻'，导致'傻逼'匹配失败）
    sensitive_words_sorted = sorted(sensitive_words, key=len, reverse=True)
    
    for word in sensitive_words_sorted:
        # 创建正则模式，\b 表示单词边界，确保是独立的一个词
        pattern = r'\b' + re.escape(word) + r'\b'
        # 生成对应数量的星号
        replacement = '*' * len(word)
        # 进行替换
        text = re.sub(pattern, replacement, text)
        
    return text

def main():
    # 1. 定义文件路径
    sensitive_file = 'sensitive_words.txt'  # 敏感词文件
    input_file = 'input.txt'               # 输入文本文件
    output_file = 'output.txt'             # 输出文本文件（可选）

    # 2. 加载敏感词
    sensitive_words = load_sensitive_words(sensitive_file)
    
    if not sensitive_words:
        return

    print(f"已加载敏感词：{sensitive_words}")

    # 3. 读取普通文本文件
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            original_text = f.read()
        print("--- 原始文本 ---")
        print(original_text)
    except FileNotFoundError:
        print(f"错误：找不到输入文件 {input_file}。")
        return

    # 4. 执行替换
    cleaned_text = replace_sensitive_words(original_text, sensitive_words)
    
    print("--- 替换后文本 ---")
    print(cleaned_text)

    # 5. (可选) 将结果保存到新文件
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(cleaned_text)
    print(f"替换完成，结果已保存至 {output_file}")

if __name__ == "__main__":
    main()
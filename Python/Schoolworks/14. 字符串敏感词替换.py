text = input()
sensitive_word = input()

if sensitive_word in text:
    replacement = '*' * len(sensitive_word)
    print(text.replace(sensitive_word,replacement))
else:
    print("无敏感词")

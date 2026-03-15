cat > README.md << EOF

# daily-code

日常练习代码合集，包含C语言、Python、前端、算法等小代码/作业。

## 目录结构

- C#：代码和笔记
- cpp：代码和笔记
- C语言: C语言基础练习、小项目
- Python: Python自动化脚本、数据分析小案例
- web-demo: 前端静态页面、JS练习
- data-structure: 数据结构与算法实现（排序、链表等）
- test: 测试/临时代码（不定期清理）

## 操作说明

- 新增代码：放入对应分类目录，执行git add/commit/push
- 查看历史：git log
- 同步备份：git pushall（已配置一键同步GitHub+Gitee）

## 日常开发操作流程（核心）

### 场景1：新增小代码（比如写一个Python计算器）

```bash
# 1. 进入对应目录
cd python

# 2. 创建/编辑文件（可手动创建，也可终端创建）
touch calculator.py  # 创建空文件，用编辑器打开写入代码

# 3. 回到仓库根目录
cd ..

# 4. 查看改动（确认新增的文件）
git status  # 红色字体显示python/calculator.py（未暂存）

# 5. 暂存文件（3种方式任选）
git add python/calculator.py  # 精准暂存单个文件
# git add python/  # 暂存python目录下所有改动
# git add .        # 暂存所有新增/修改的文件（推荐日常用）

# 6. 提交（备注格式：类型: 描述，比如feat: 新增Python计算器脚本）
git commit -m "feat: 新增Python计算器脚本（支持加减乘除）"

# 7. 推送到远程（GitHub）
git push

# 可选：一键同步GitHub+Gitee
git pushall
```

### 场景2：修改已有代码（比如优化计算器脚本）

```bash
# 1. 编辑python/calculator.py（修改代码）

# 2. 查看改动
git status  # 显示python/calculator.py已修改

# 3. 暂存+提交
git add .
git commit -m "fix: 修复Python计算器除法除零错误"

# 4. 推送
git push  # 或git pushall
```

### 场景3：删除无用代码（比如test目录下的临时文件）

```bash
# 1. 删除文件（终端/手动删除均可）
rm test/scratch.py

# 2. 暂存删除操作
git add .

# 3. 提交
git commit -m "clean: 删除test目录下无用的临时测试文件"

# 4. 推送
git push
```

### 场景4：拉取远程最新代码（多人协作/多设备同步）

如果在另一台电脑修改了代码并推送，本地需先拉取最新版本：

```bash
# 进入仓库根目录
cd ~/Documents/code/daily-code

# 拉取GitHub最新代码
git pull origin main

# 可选：拉取Gitee最新代码（若在Gitee修改过）
git pull gitee main
```

## 进阶操作（解决问题/优化管理）

### 1. 撤销误操作

#### （1）撤销未暂存的修改（比如改坏了代码，想恢复）

```bash
# 恢复单个文件（比如python/calculator.py）
git checkout -- python/calculator.py

# 恢复所有未暂存的修改
git checkout -- .
```

#### （2）撤销已暂存但未提交的文件

```bash
# 撤销单个文件的暂存
git reset HEAD python/calculator.py

# 撤销所有暂存的文件
git reset HEAD .
```

#### （3）回滚已提交的版本（比如提交了错误代码）

```bash
# 查看提交历史（找到要回滚的版本号，前7位即可）
git log  # 输出示例：commit 1234567 (HEAD -> main) ...

# 回滚到指定版本（保留代码，仅撤销提交记录）
git reset --soft 1234567

# 彻底回滚（删除提交记录+恢复代码，谨慎使用）
git reset --hard 1234567
```

### 2. 分支管理（用于测试/临时功能）

日常小代码建议用main分支即可，如需测试新功能，可创建临时分支：

```bash
# 创建并切换到临时分支（比如test-sort）
git checkout -b test-sort

# 在分支上开发（比如写排序算法）
# ... 开发完成后 ...

# 切回main分支
git checkout main

# 合并分支（将test-sort的改动合并到main）
git merge test-sort

# 删除临时分支（可选）
git branch -d test-sort

# 推送合并后的main分支
git push
```

### 3. 定期清理仓库

- 清理test目录下的无用临时文件；
- 删除已合并的临时分支；
- 定期更新README.md，补充新增的目录/代码说明。

## 常见问题与解决

### 问题1：推送失败（提示权限拒绝）

- 原因：GitHub密码登录已停用，需用Personal Access Token（PAT）；
- 解决：
  1. 登录GitHub → 右上角头像 → Settings → Developer settings → Personal access tokens → Generate new token；
  2. 勾选权限：`repo`（全选），设置有效期（建议选No expiration）；
  3. 生成后复制token（仅显示一次，务必保存）；
  4. 推送时，用户名填GitHub账号，密码填该token。

### 问题2：推送冲突（远程仓库有本地没有的改动）

```bash
# 先拉取远程代码并合并（允许无关历史）
git pull origin main --allow-unrelated-histories

# 手动解决冲突（编辑器会标记冲突区域，保留需要的代码）
# 解决后暂存+提交
git add .
git commit -m "merge: 解决远程与本地代码冲突"

# 重新推送
git push
```

### 问题3：git add . 误加了无用文件

```bash
# 撤销暂存
git reset HEAD 无用文件名

# 确认.gitignore已配置该文件，避免下次误加
```

## 七、规范建议（便于长期维护）

1. **提交信息规范**：用「类型: 描述」格式，比如：
   - feat: 新增功能（如新增Python脚本）；
   - fix: 修复bug（如修复计算器除零错误）；
   - clean: 清理文件（如删除临时代码）；
   - docs: 更新文档（如修改README.md）；
   - init: 初始化（首次提交）。
2. **目录管理**：每个子目录可加简短的README.md，记录该目录下代码的用途、运行方式；
3. **定期备份**：至少每周推送一次代码，重要代码同步到Gitee；
4. **避免大文件**：仓库只存代码文件，不存视频、大日志、编译后的二进制文件（可通过.gitignore屏蔽）。

当然可以！当 `git pushall` 一键同步失败时（比如 GitHub 网络超时、Gitee 权限问题），只需单独推送失败的平台即可，我给你整理了**精准、好记的单独重推命令**，还会说明常见失败原因和解决思路。

### 一、单独推送指定平台的核心命令

#### 1. 只推送到 GitHub（忽略 Gitee）

```bash
# 基础版（默认推main分支）
git push origin main

# 兜底版（强制指定分支，避免分支名不一致导致失败）
git push origin HEAD:main
```

#### 2. 只推送到 Gitee（忽略 GitHub）

```bash
# 基础版（默认推main分支）
git push gitee main

# 兜底版（强制指定分支）
git push gitee HEAD:main
```

> 💡 小技巧：`HEAD` 代表「当前所在分支」，用 `HEAD:main` 可以避免因不小心切到其他分支（比如 test 分支）而推错分支的问题，新手推荐用兜底版。

### 二、常见失败场景 + 对应重推方案（直接照做）

| 失败场景              | 报错特征                              | 重推命令                                   | 额外解决思路                           |
| ----------------- | --------------------------------- | -------------------------------------- | -------------------------------- |
| GitHub 网络超时/打不开   | `Failed to connect to github.com` | `git push origin main`                 | 切换手机热点/配置 Git 代理（国内访问 GitHub 常用） |
| Gitee 权限拒绝        | `Permission denied`               | `git push gitee main`                  | 检查 Gitee 的 SSH 公钥/PAT 是否过期       |
| 分支名不一致（比如用master） | `refspec main does not match`     | `git push origin HEAD:master`          | 把命令里的 `main` 换成实际分支名（如master）    |
| 本地代码落后于远程         | `non-fast-forward`                | `git pull 平台名 分支名 && git push 平台名 分支名` | 先拉取远程最新代码合并，再推送                  |

#### 示例：解决「本地代码落后于远程」的重推

比如推 GitHub 时提示「代码落后」，执行：

```bash
# 先拉取GitHub最新代码（合并冲突后）
git pull origin main
# 再单独推GitHub
git push origin main
```

### 三、验证推送是否成功

推送后，可通过以下命令确认本地代码和远程同步：

```bash
# 查看GitHub远程分支状态
git fetch origin
git log origin/main..main  # 无输出=本地和GitHub同步

# 查看Gitee远程分支状态
git fetch gitee
git log gitee/main..main   # 无输出=本地和Gitee同步
```

### 总结

1. 单独推 GitHub：`git push origin main`
2. 单独推 Gitee：`git push gitee main`
3. 代码落后先拉再推：`git pull 平台名 main && git push 平台名 main`
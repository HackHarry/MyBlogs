## Git操作与使用整理汇总

### 前言

因笔者对于git和github操作的不熟练，本文用于整理汇总Git以及Github的使用操作，方便随时翻阅查看。



### Git基础命令

#### git init

初始化git仓库

#### git status

查看git仓库的状态

#### git add

将未提交到git仓库里的内容（增删改）添加到缓存中

可以使用git rm --cached这个命令来移除这个缓存

#### git commit

提交缓存区的内容到git仓库中。

git commit -m ‘first commit’，-m表示附带的提交信息

#### git log

查看所有产生的commit记录



### Git与Github

若要让本地仓库与GitHub远程仓库联系，需要SSH密钥

#### ssh -T git@github.com

测试是否成功添加成功SSH key

#### git pull

git pull origin master，将远程最新代码更新到本地

#### git push

git push origin master，将本地代码推送到远程仓库的master分支中

#### git clone

git clone 远程仓库地址，将远程仓库clone到本地

#### git remote

git remote add origin 远程仓库地址，给项目添加一个名为origin的远程仓库

**git remote -v**，可以查看当前项目有哪些远程仓库



### Git分支操作

执行git init初始化git仓库之后，会默认生成一个主分支master，这个分支可以看成是实际开发正式环境下的分支，一般情况下是不会轻易在master分支上面操作的。为了防止对代码的修改影响正式版本，需要在新建的分支上进行修改操作，测试通过后再合并到master分支中。

#### git branch

基于当前分支新建分支，如git branch a，新建名为a的分支

若只输入git branch，表示查看当前分支情况

#### git tag

新建标签，一般用于标记代码版本，如git tag v1.0表示将当前代码状态标记为v1.0

若只输入git tag，表示查看历史tag记录

#### git checkout

切换

如git checkout a，切换到a分支

git checkout v1.0，表示切换到tag为v1.0的版本

git checkout 文件名，撤销还未add进暂存区的文件

#### git checkout -b a

新建并切换到分支a

#### git merge 

合并分支，如git merge a，合并a分支到当前分支

#### git branch -d

删除分支，如git branch -d a

git branch -D为强制删除操作

1. Set up a CI server
   * do daily builds
   * merge latest changes from LLVM master to our fork
   ```
   # See https://help.github.com/en/articles/merging-an-upstream-repository-into-your-fork
   # In a repo initialized using
   # git clone https://github.com/gaps-closure/llvm-project.git
   cd llvm-project
   git checkout master
   git pull https://github.com/llvm/llvm-project.git master
   # Resolve any conflicts from the merge, test the code
   git commit
   git push origin master
   ```
   * ...
 

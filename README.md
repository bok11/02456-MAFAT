# 02456-MAFAT
COFGA dataset


## Commits
Commits cannot be made directly to master, but must instead be commited to secondary branches.

## Pull requests
When a pull request is made, the convention is as follows:  
**NAME:** Name the request after the implemented feature  
**Assignee:** Assign yourself as owner  
**Project:** Assign the pull request to a project if applicable  

When a pull request is merged, the branch gets deleted.

## How to delete a local branch and start a new one
This applies mostly when a pull request is merged, and you want to start over from master.

```bash
git checkout master
git branch -d <Branchname>
git fetch -p
git checkout -b <Branchname>
git push --set-upstream origin <Branchname>
```
You now deleted your old branch, and created a new one at (both local and on github)

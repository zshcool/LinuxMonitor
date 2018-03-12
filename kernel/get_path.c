#include "get_path.h"
#include <linux/path.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
void set_fs_pwd_user(struct fs_struct *fs, struct path *path)
{
	struct path old_pwd;

	write_lock(&fs->lock);
	old_pwd = fs->pwd;
	fs->pwd = *path;
	path_get(path);
	write_unlock(&fs->lock);

	if (old_pwd.dentry)
		path_put(&old_pwd);
}
#endif


char* get_absolute_path(struct task_struct * task)
{
    char * ret_ptr = NULL;
    char * tpath   = NULL ;
    struct vm_area_struct * vma = NULL;
    struct path base_path;

    tpath = (char*)kmalloc(512, 0);
    if(NULL == tpath || NULL == task)
    {
        return NULL;
    }
    memset(tpath,'\0',512);

    task_lock(task);
    /* 
    获取当前进程的内存空间信息(通过内存空间)
    */
    if(task->mm && task->mm->mmap)
    {
        vma = task->mm->mmap;
    }
    else
    {
        task_unlock(task);
        kfree(tpath);
        return NULL;
    }

    /*
    取得path(a struct含dentry和vfsmount)
    */
    while(vma)
    {
        if ((vma->vm_flags & VM_EXEC) && vma->vm_file)
        {    
            base_path = vma->vm_file->f_path;
            break;
        }
        vma = vma->vm_next;
    }
    task_unlock(task);

    /*
     * 调用 d_path, 得到绝对路径
     */
    ret_ptr = d_path(&base_path, tpath, 512);
    kfree(tpath);

    return ret_ptr;
} 




struct path_name_node* get_name_node(void)
{
    struct path_name_node* node;
    node = (struct path_name_node*)vmalloc(sizeof(struct path_name_node));
    if (node == NULL) return NULL;
    node->next = NULL;

    return node;
}


int not_root_name(struct dentry * d)
{
    return strcmp(d->d_name.name, ROOT_PATH) != 0;
}

struct path_name_node * get_name_node_list(struct dentry * d)
{
    struct path_name_node head;
    struct path_name_node *cur;
    struct dentry *tmp_d = d;

    if (d == NULL) return NULL;

    head.next = NULL;

    while(not_root_name(tmp_d))
    {
        cur = get_name_node();
        if (cur == NULL) break;
        strcpy(cur->name, tmp_d->d_name.name);
        cur->next = head.next;
        head.next = cur;
        tmp_d = tmp_d->d_parent;
    }
    
    return head.next;
}


void remove_node_list(struct path_name_node *node)
{
    struct path_name_node *cur = node;
    struct path_name_node *tmp;
    while(cur)
    {
        tmp = cur;
        cur = cur->next;
        vfree(tmp);
    }
}


void get_pwd(struct task_struct * task, char *buf, int size)
{
    int pos = 0;
    struct path pwd;
    struct path_name_node * head;
    struct path_name_node * cur;

#if LINUX_VERSION_CODE>= KERNEL_VERSION(3,0,0)
    get_fs_pwd(task->fs, &pwd);
#else
    set_fs_pwd_user(task->fs, &pwd);
#endif

    head = get_name_node_list(pwd.dentry);
    cur = head;

    while(cur)
    {
        int len = strlen(cur->name);
        if (pos + len + 2 > size)
            break;
        buf[pos] = '/';
        strcpy(buf + pos + 1, cur->name);
        pos += (len + 1);
        cur = cur->next;
    }

    buf[pos] = 0x00;

    remove_node_list(head);
}

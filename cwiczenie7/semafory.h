typedef int sem;
sem sem_create(const char *file, char p, int sem_count);
void set_val(sem sem_id, int sem_num, int val);
int get_val(sem sem_id, int sem_num);
int get_ncnt(sem sem_id, int sem_num);
int get_zcnt(sem sem_id, int sem_num);
void sem_delete(sem sem_id);
void get_down(sem sem_id, int sem_num);
void get_up(sem sem_id, int sem_num);
void sem_describe(sem semid, int i);


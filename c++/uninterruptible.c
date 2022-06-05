/* uninterruptible.c sleep d-state */

int main() {
    vfork();
    sleep(300);
    return 0;
}

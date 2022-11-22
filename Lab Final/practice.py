from multiprocessing import Process, Pipe
from time import sleep


def worker(id, task):
    # sleep(1)
    print(f"I am process {id}, doing {task}")

    with open(task+".txt", "w") as fh:
        fh.write(task)


if __name__ == "__main__":

    print("Master process started")

    process_list: list[Process] = []
    action_dict = {
        1: "palindrome_checking",
        2: "password_strngth_checking",
        3: "prime_number_generation"
    }

    for i in range(1, 4):
        process_list.append(
            Process(target=worker, args=(i, action_dict[i]))
        )

    for process in process_list:
        process.start()

    for process in process_list:
        process.join()

    print("Master process ended")

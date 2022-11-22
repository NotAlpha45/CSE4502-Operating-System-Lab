from multiprocessing import Process, JoinableQueue, current_process, parent_process
from queue import Empty
from threading import Thread, current_thread


def process_worker(queue: JoinableQueue):

    try:
        item = queue.get()
        id = item.get('id')
        task = item.get('task')
        filename = item.get('filename')

        process_id = current_process().pid

        print(f"I am process: {id}, process id: {process_id}, doing: {task}")
        print(f"My parent: {parent_process().pid}")
        print()

        with open(filename, "w") as fh:
            fh.write(task)

        # The enqued data has been read
        queue.task_done()

    except Empty:
        print("The queue is empty")
        pass


def thread_worker(thread_id: int, filename: str):
    with open(filename, "r") as fh:
        print(f"I am {thread_id}. My assigned task: {fh.read()}")


if __name__ == "__main__":

    print(f"Master process started, process id: {current_process().pid}\n")

    process_list: list[Process] = []
    thread_list: list[Thread] = []

    action_dict = {
        1: "palindrome_checking",
        2: "password_strngth_checking",
        3: "prime_number_generation"
    }

    communication_queue = JoinableQueue()

    for i in range(1, 4):

        communication_queue.put({
            "id": i,
            "task": action_dict[i],
            "filename": action_dict[i] + ".txt"
        })

        process_list.append(
            Process(target=process_worker, args=(communication_queue,))
        )

    for process in process_list:
        process.start()

    # Wait for the processes to finish
    for process in process_list:
        process.join()

    for i in range(1, 4):
        thread_list.append(
            Thread(target=thread_worker, args=(i, ))
        )

    print("Master process ended")

from multiprocessing import Process, JoinableQueue, current_process, parent_process
from queue import Empty


def worker(queue: JoinableQueue):

    try:
        item = queue.get()
        id = item.get('id')
        task = item.get('task')

        # The enqued data has been read
        queue.task_done()

        process_id = current_process().pid

        print(f"I am process: {id}, process id: {process_id}, doing: {task}")
        print(f"My parent: {parent_process().pid}")
        print()

        with open(task+".txt", "w") as fh:
            fh.write(task)

    except Empty:
        print("The queue is empty")
        pass


if __name__ == "__main__":

    print(f"Master process started, process id: {current_process().pid}")

    process_list: list[Process] = []

    action_dict = {
        1: "palindrome_checking",
        2: "password_strngth_checking",
        3: "prime_number_generation"
    }

    communication_queue = JoinableQueue()

    for i in range(1, 4):

        communication_queue.put({
            "id": i,
            "task": action_dict[i]
        })

        process_list.append(
            Process(target=worker, args=(communication_queue,))
        )

    for process in process_list:
        process.start()

    # Wait for the processes to finish
    for process in process_list:
        process.join()

    print("Master process ended")

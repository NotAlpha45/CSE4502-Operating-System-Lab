from Process import Process

process_dict = dict()

no_of_process: int = int(input("Enter the no. of process: "))
total_processes = no_of_process

while no_of_process:
    process_id, burst_time, priority, arrival_time = map(str, input(
        "Enter process ID, burst time, priority and arrival time: ").split())

    process_dict[process_id] = Process(
        process_id=process_id,
        burst_time=float(burst_time),
        priority=int(priority),
        arrival_time=float(arrival_time)
    )
    no_of_process -= 1

current_time = 0
net_waiting_time = 0
net_response_time = 0

result_order = ""
result_list: list[Process] = []

while process_dict:

    current_processes: list[Process] = [
        process for process in process_dict.values() if process.arrival_time <= current_time]

    current_processes.sort(key=lambda process: process.burst_time)

    for process in current_processes:

        process.start_time = current_time

        process.response_time = current_time - process.arrival_time

        current_time += process.burst_time

        process.end_time = current_time

        process.turnaround_time = process.end_time - process.arrival_time
        process.waiting_time = process.turnaround_time - process.burst_time
        process.response_time = process.start_time - process.arrival_time

        net_waiting_time += process.waiting_time
        net_response_time += process.response_time

        result_order += f"{process.process_id} -> "
        print(process.process_id)

        result_list.append(process)

        del process_dict[process.process_id]

print(current_time)

print(result_order)
print()
for result in result_list:
    print(result.process_id)
    print(f"Arrival Time {result.arrival_time}")
    print(f"Start Time : {result.start_time}")
    print(f"End Time: {result.end_time}")
    print(f"Trunaround Time {result.turnaround_time}")
    print(f"Response Time: {result.response_time}")
    print(f"Waiting Time: {result.waiting_time}")
    print()

print(f"Average response time: {net_response_time/total_processes}")
print(f"Average waiting time: {net_waiting_time/total_processes}")

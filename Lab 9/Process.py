class Process():

    def __init__(self, process_id: str, burst_time: float, priority: int, arrival_time: float):
        self.process_id: str = process_id
        self.burst_time: float = burst_time
        self.arrival_time: float = arrival_time
        self.priority: int = priority

        self.start_time: float = None
        self.end_time: float = None

        self.turnaround_time: float = None
        self.waiting_time: float = None
        self.response_time: float = None

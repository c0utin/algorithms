struct Queue<T> {
    data: Vec<T>,
}

impl<T> Queue<T> {
    fn new() -> Self {
        Self { data: Vec::new() }
    }

    fn enqueue(&mut self, value: T) {
        self.data.push(value);
    }

    fn dequeue(&mut self) -> Option<T> {
        if self.data.is_empty() {
            None
        } else {
            Some(self.data.remove(0))
        }
    }

    fn peek(&self) -> Option<&T> {
        self.data.first()
    }
}

fn main() {
    let mut queue = Queue::new();
    queue.enqueue(1);
    queue.enqueue(2);
    println!("first {:?}", queue.peek());
    queue.dequeue();
    println!("dequeue: {:?}", queue.peek());
}

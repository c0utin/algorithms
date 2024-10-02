fn buble_sort(arr: &mut [u8; 5]){

    for i in 0..arr.len(){
        for j in 0..arr.len() - i - 1 {
            if arr[j] > arr[j+1] {
                arr.swap(j, j + 1);
            }
        }
    }
}

fn main() {

    let mut arr: [u8; 5] = [1,69,2,7,4];
    
    buble_sort(&mut arr);
    assert_eq!(arr, [1,2,4,7,69], "vish");

    println!("{:?}", arr);
}


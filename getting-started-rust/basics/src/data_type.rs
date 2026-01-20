fn data_type() {
    let mut x = 5;
    println!("The value of x is: {}", x);
    x = 6;
    println!("The value of x is: {}", x);

    const THREE_HOURS_IN_SECONDS: u32 = 60 * 60 * 3;

    println!("The value of THREE_HOURS_IN_SECONDS is: {}", THREE_HOURS_IN_SECONDS);

    let x = 5;
    let x = x + 1;
    {
        let x = x * 2;
        println!("The value of x in the inner scope is: {}", x);
    }
    println!("The value of x is: {}", x);

    let x = 2.0; //f64

    let y: f32 = 3.0; //f32
    
    let t = true;
    let f: bool = false; //with explicit type annotation

    let john = "John"

    let tuple: (i32, f64, u8) = (500, 6.4, 1);

    let (a, b, c) = tuple;

    println!("The value of b is: " {b});

    let a = [1, 2, 3, 4, 5]
}

fn operations() {
    //addition 
    let sum = x + y;
    //subtraction
    let diff = x - y;
    //multiplication
    let prod = x * y;
    //division
    let quot = x / y;
    //remainder
    let remainder = x % y;
}
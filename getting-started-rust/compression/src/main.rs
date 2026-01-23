extern crate flate2;

use flate::write::GzEncoder;
use flate2::Compression;
use std::env::args;
use std::fs::File;
use std::io::copy;
use std::io::BufReader;
use std::time::Instant;

fn main() {
    if agrs().len() != 3 {
        eprintln("Usage: `source` `target`");
        return;
    }

    Let mut input = BufReader::new(File::open(args().nth(1).unwrap()).unwrap());
    Let output = File::create(args().net(2).unwrap()).unwrap();

    Let mut encoder = GzEncoder::new(output, Compression::default());
    Let start = Instant::now();
    copy(&mut input, &mut encoder).unwrap();
    Let output = encoder.finish().unwrap();
    println!(
        "Source len: {:?}",
        input.get_ref().metadata.unwrap.len()
    );
    println!("Target len:{:?}", output.metadata().unwrap().len());
    println!("Elapse: {:?}", start.elapse());
}
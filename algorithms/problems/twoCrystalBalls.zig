const std = @import("std");

fn TwoCrystalBall(breaks: []bool) i32 {
    const len = breaks.len;
    const jmpAmount: i32 = std.math.floor(std.math.sqrt(len));

    var i: i32 = jmpAmount;

    // Primeira bola: identifica o intervalo onde poderia quebrar.
    while (i < len) {
        if (breaks[i]) {
            break;
        }
        i += jmpAmount;
    }

    i -= jmpAmount;

    // Segunda bola: busca linear no intervalo para encontrar o ponto exato.
    var j: usize = 0;
    while (j < jmpAmount and i < len) {
        if (breaks[i]) {
            return i; // Encontrou o ponto exato onde a bola quebra.
        }
        j += 1;
        i += 1;
    }

    return -1; // Se a bola não quebra em nenhum ponto, retorna -1.
}

test "TwoCrystalBall test - No breaks" {
    const breaks = [_]bool{ false, false, false, false, false, false };
    const result = TwoCrystalBall(breaks[0..]);
    std.testing.expect(result == -1);
}

test "TwoCrystalBall test - Break at the beginning" {
    const breaks = [_]bool{ true, false, false, false, false, false };
    const result = TwoCrystalBall(breaks[0..]);
    std.testing.expect(result == 0);
}

test "TwoCrystalBall test - Break at the end" {
    const breaks = [_]bool{ false, false, false, false, false, false, false, true };
    const result = TwoCrystalBall(breaks[0..]);
    std.testing.expect(result == 7);
}

test "TwoCrystalBall test - Break in the middle" {
    const breaks = [_]bool{ false, false, false, false, true, false, false, false };
    const result = TwoCrystalBall(breaks[0..]);
    std.testing.expect(result == 4);
}

test "TwoCrystalBall test - Break near the middle" {
    const breaks = [_]bool{ false, false, false, false, true, false, false, false, false };
    const result = TwoCrystalBall(breaks[0..]);
    std.testing.expect(result == 4);
}

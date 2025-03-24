options gen2
require minfft
require math

[export]
def main {
    var signal <- [ for (i in range(64)); sin(float(i) * 0.2) ]
    var complex_frequencies : array<float2>
    fft_real_forward(signal, complex_frequencies)
    for (f in complex_frequencies) {
        print("r = {f.x}  i = {f.y}\n")
    }
}

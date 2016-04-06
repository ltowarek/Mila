import csv
import re
import subprocess

if __name__ == '__main__':
    cases = [
        'mean_shift_sequential.exe test_image_63x47.png test_image_63x47_sequential_output.png 5.0 10',
        'mean_shift_parallel.exe test_image_63x47.png test_image_63x47_parallel_output.png 5.0 0 0 10',
        'mean_shift_sequential.exe test_image_63x47.png test_image_63x47_sequential_output.png 10.0 10',
        'mean_shift_parallel.exe test_image_63x47.png test_image_63x47_parallel_output.png 10.0 0 0 10',
        'mean_shift_sequential.exe test_image_63x47.png test_image_63x47_sequential_output.png 20.0 10',
        'mean_shift_parallel.exe test_image_63x47.png test_image_63x47_parallel_output.png 20.0 0 0 10',
        'mean_shift_sequential.exe test_image_63x47.png test_image_63x47_sequential_output.png 40.0 10',
        'mean_shift_parallel.exe test_image_63x47.png test_image_63x47_parallel_output.png 40.0 0 0 10',
        'mean_shift_sequential.exe test_image_63x47.png test_image_63x47_sequential_output.png 80.0 10',
        'mean_shift_parallel.exe test_image_63x47.png test_image_63x47_parallel_output.png 80.0 0 0 10',
        'mean_shift_sequential.exe test_image_63x47.png test_image_63x47_sequential_output.png 160.0 10',
        'mean_shift_parallel.exe test_image_63x47.png test_image_63x47_parallel_output.png 160.0 0 0 10',

        'mean_shift_sequential.exe test_image_32x24.png test_image_32x24_sequential_output.png 25.0 10',
        'mean_shift_parallel.exe test_image_32x24.png test_image_32x24_parallel_output.png 25.0 0 0 10',
        'mean_shift_sequential.exe test_image_63x47.png test_image_63x47_sequential_output.png 25.0 10',
        'mean_shift_parallel.exe test_image_63x47.png test_image_63x47_parallel_output.png 25.0 0 0 10',
        'mean_shift_sequential.exe test_image_125x94.png test_image_125x94_sequential_output.png 25.0 10',
        'mean_shift_parallel.exe test_image_125x94.png test_image_125x94_parallel_output.png 25.0 0 0 10',
        'mean_shift_sequential.exe test_image_250x188.png test_image_250x188_sequential_output.png 25.0 10',
        'mean_shift_parallel.exe test_image_250x188.png test_image_250x188_parallel_output.png 25.0 0 0 10',
    ]

    results = []

    for case in cases:
        try:
            output = subprocess.check_output(case, shell=True, stderr=subprocess.STDOUT, universal_newlines=True)
        except subprocess.CalledProcessError as error:
            print('Error occurred!')
            output = error.output

        print(output)

        device_name = ''
        m = re.search(r'Device: (.*)', output, re.MULTILINE)
        if m:
            device_name = m.group(1)

        input_file = ''
        m = re.search(r'Input file: (.*)', output, re.MULTILINE)
        if m:
            input_file = m.group(1)

        output_file = ''
        m = re.search(r'Output file: (.*)', output, re.MULTILINE)
        if m:
            output_file = m.group(1)

        image_size = 0
        m = re.search(r'(\d+)x(\d+)', input_file)
        if m:
            image_size = int(m.group(1)) * int(m.group(2))

        bandwidth = 0.0
        m = re.search(r'Bandwidth: (.*)', output, re.MULTILINE)
        if m:
            bandwidth = float(m.group(1))

        mean = 0.0
        m = re.search(r'Mean: (.*)', output, re.MULTILINE)
        if m:
            mean = float(m.group(1))

        median = 0.0
        m = re.search(r'Median: (.*)', output, re.MULTILINE)
        if m:
            median = float(m.group(1))

        variance = 0.0
        m = re.search(r'Variance: (.*)', output, re.MULTILINE)
        if m:
            variance = float(m.group(1))

        standard_deviation = 0.0
        m = re.search(r'Standard Deviation: (.*)', output, re.MULTILINE)
        if m:
            standard_deviation = float(m.group(1))

        coefficient_of_variation = 0.0
        m = re.search(r'Coefficient of Variation: (.*)', output, re.MULTILINE)
        if m:
            coefficient_of_variation = float(m.group(1))

        results.append({'Nazwa urządzenia': device_name,
                        'Plik wejściowy': input_file,
                        'Plik wyjściowy': output_file,
                        'Rozmiar obrazka': image_size,
                        'Rozmiar okna': bandwidth,
                        'Średnia[us]': mean,
                        'Mediana[us]': median,
                        'Standardowe odchylenie[us]': standard_deviation,
                        'Kowariancja': coefficient_of_variation,
                        'CMD': case})

    with open('results.csv', 'wt', encoding='utf-8', newline='') as results_file:
        csv_writer = csv.DictWriter(results_file,
                                    ['Nazwa urządzenia', 'Plik wejściowy', 'Plik wyjściowy', 'Rozmiar obrazka', 'Rozmiar okna', 'Średnia[us]', 'Mediana[us]', 'Standardowe odchylenie[us]', 'Kowariancja', 'CMD'])
        csv_writer.writeheader()
        csv_writer.writerows(results)

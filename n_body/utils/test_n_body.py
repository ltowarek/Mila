import csv
import re
import subprocess

if __name__ == '__main__':
    cases = [
        'n_body_sequential.exe test_input_100.txt 200 10',
        'n_body_sequential.exe test_input_100.txt 400 10',
        'n_body_sequential.exe test_input_100.txt 800 10',
        'n_body_sequential.exe test_input_100.txt 1600 10',
        'n_body_sequential.exe test_input_100.txt 3200 10',
        'n_body_sequential.exe test_input_100.txt 6400 10',

        'n_body_parallel.exe test_input_100.txt 200 1 1 10',
        'n_body_parallel.exe test_input_100.txt 400 1 1 10',
        'n_body_parallel.exe test_input_100.txt 800 1 1 10',
        'n_body_parallel.exe test_input_100.txt 1600 1 1 10',
        'n_body_parallel.exe test_input_100.txt 3200 1 1 10',
        'n_body_parallel.exe test_input_100.txt 6400 1 1 10'
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

        number_of_frames = 0
        m = re.search(r'(\d+)', input_file)
        if m:
            number_of_frames = int(m.group(1))

        number_of_particles = 0
        m = re.search(r'Number of particles: (.*)', output, re.MULTILINE)
        if m:
            number_of_particles = int(m.group(1))

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
                        'Liczba klatek': number_of_frames,
                        'Liczba cząsteczek': number_of_particles,
                        'Średnia[us]': mean,
                        'Mediana[us]': median,
                        'Standardowe odchylenie[us]': standard_deviation,
                        'Kowariancja': coefficient_of_variation,
                        'CMD': case})

    with open('results_n_body.csv', 'wt', encoding='utf-8', newline='') as results_file:
        csv_writer = csv.DictWriter(results_file,
                                    ['Nazwa urządzenia', 'Plik wejściowy', 'Liczba klatek', 'Liczba cząsteczek',
                                     'Średnia[us]', 'Mediana[us]', 'Standardowe odchylenie[us]', 'Kowariancja', 'CMD'])
        csv_writer.writeheader()
        csv_writer.writerows(results)

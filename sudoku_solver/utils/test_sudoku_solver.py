import csv
import re
import subprocess

if __name__ == '__main__':
    cases = [
        'sudoku_solver_sequential.exe ai_escargot.txt ai_escargot_sequential_output.txt 10',
        'sudoku_solver_sequential.exe easter_monster.txt easter_monster_sequential_output.txt 10',
        'sudoku_solver_sequential.exe golden_nugget.txt golden_nugget_sequential_output.txt 10',
        'sudoku_solver_sequential.exe hard_for_brute_force.txt hard_for_brute_force_sequential_output.txt 10',

        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_1_output.txt 1 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_2_output.txt 2 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_3_output.txt 3 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_4_output.txt 4 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_5_output.txt 5 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_6_output.txt 6 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_7_output.txt 7 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_8_output.txt 8 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_9_output.txt 9 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_10_output.txt 10 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_11_output.txt 11 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_12_output.txt 12 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_13_output.txt 13 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_14_output.txt 14 1 1 10',
        'sudoku_solver_parallel.exe ai_escargot.txt ai_escargot_parallel_15_output.txt 15 1 1 10',

        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_1_output.txt 1 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_2_output.txt 2 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_3_output.txt 3 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_4_output.txt 4 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_5_output.txt 5 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_6_output.txt 6 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_7_output.txt 7 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_8_output.txt 8 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_9_output.txt 9 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_10_output.txt 10 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_11_output.txt 11 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_12_output.txt 12 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_13_output.txt 13 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_14_output.txt 14 1 1 10',
        'sudoku_solver_parallel.exe easter_monster.txt easter_monster_parallel_15_output.txt 15 1 1 10',

        'sudoku_solver_parallel.exe golden_nugget.txt golden_nugget_parallel_1_output.txt 1 1 1 10',
        'sudoku_solver_parallel.exe golden_nugget.txt golden_nugget_parallel_2_output.txt 2 1 1 10',
        'sudoku_solver_parallel.exe golden_nugget.txt golden_nugget_parallel_3_output.txt 3 1 1 10',
        'sudoku_solver_parallel.exe golden_nugget.txt golden_nugget_parallel_4_output.txt 4 1 1 10',
        'sudoku_solver_parallel.exe golden_nugget.txt golden_nugget_parallel_5_output.txt 5 1 1 10',
        'sudoku_solver_parallel.exe golden_nugget.txt golden_nugget_parallel_6_output.txt 6 1 1 10',
        'sudoku_solver_parallel.exe golden_nugget.txt golden_nugget_parallel_7_output.txt 7 1 1 10',
        'sudoku_solver_parallel.exe golden_nugget.txt golden_nugget_parallel_8_output.txt 8 1 1 10',
        'sudoku_solver_parallel.exe golden_nugget.txt golden_nugget_parallel_9_output.txt 9 1 1 10',
        'sudoku_solver_parallel.exe golden_nugget.txt golden_nugget_parallel_10_output.txt 10 1 1 10',

        'sudoku_solver_parallel.exe hard_for_brute_force.txt hard_for_brute_force_parallel_1_output.txt 1 1 1 10',
        'sudoku_solver_parallel.exe hard_for_brute_force.txt hard_for_brute_force_parallel_2_output.txt 2 1 1 10',
        'sudoku_solver_parallel.exe hard_for_brute_force.txt hard_for_brute_force_parallel_3_output.txt 3 1 1 10',
        'sudoku_solver_parallel.exe hard_for_brute_force.txt hard_for_brute_force_parallel_4_output.txt 4 1 1 10',
        'sudoku_solver_parallel.exe hard_for_brute_force.txt hard_for_brute_force_parallel_5_output.txt 5 1 1 10',
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

        number_of_filled_cells = 0
        m = re.search(r'Number of filled cells: (.*)', output, re.MULTILINE)
        if m:
            number_of_filled_cells = int(m.group(1))

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
                        'Liczba uzupełnionych pól': number_of_filled_cells,
                        'Średnia[us]': mean,
                        'Mediana[us]': median,
                        'Standardowe odchylenie[us]': standard_deviation,
                        'Kowariancja': coefficient_of_variation,
                        'CMD': case})

    with open('results_sudoku_solver.csv', 'wt', encoding='utf-8', newline='') as results_file:
        csv_writer = csv.DictWriter(results_file,
                                    ['Nazwa urządzenia', 'Plik wejściowy', 'Plik wyjściowy', 'Liczba uzupełnionych pól', 'Średnia[us]', 'Mediana[us]', 'Standardowe odchylenie[us]', 'Kowariancja', 'CMD'])
        csv_writer.writeheader()
        csv_writer.writerows(results)

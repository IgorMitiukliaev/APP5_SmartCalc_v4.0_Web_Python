
function loadJson(selector) {
    return JSON.parse($(selector).attr('data_json'));
}

$(document).ready(function () {

    function make_chart() {
        let jsonData = loadJson('#jsonData');
        let data = jsonData.map((item) => item.y);
        let labels = jsonData.map((item) => item.x);

        let sorted = [...data];
        sorted.sort((a, b) => { return a - b; });
        let y_min = sorted.at(0), y_max = sorted.at(sorted.length - 1)*1.1;

        let config = {
            type: 'line',
            data: {
                labels: labels,
                datasets: [
                    {
                        label: 'chart',
                        backgroundColor: 'black',
                        borderColor: 'lightblue',
                        data: data,
                        fill: false,
                        spanGaps: 10
                    }
                ]
            },
            options: {
                responsive: true,
                scales: {
                    y: {
                        min: y_min,
                        max: y_max,
                    }
                }
            }
        };

        var ctx = document.getElementById('chart').getContext('2d');
        window.myLine = new Chart(ctx, config);
    }

        make_chart()
    });



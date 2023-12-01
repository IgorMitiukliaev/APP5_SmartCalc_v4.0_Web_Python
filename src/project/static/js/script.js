$(document).ready(function () {
    let dict = {
        "0": "0",
        "1": "1",
        "2": "2",
        "3": "3",
        "4": "4",
        "5": "5",
        "6": "6",
        "7": "7",
        "8": "8",
        "9": "9",
        ".": ".",
        "+": "+",
        "-": "-",
        "*": "*",
        "/": "/",
        "(": "(",
        ")": ")",
        "acos": "acos",
        "asin": "asin",
        "asin": "asin",
        "atan": "atan",
        "sqrt": "sqrt",
        "sin": "sin",
        "cos": "cos",
        "tan": "tan",
        "log": "log",
        "ln": "ln",
        "X": "x",
        "mod": "mod",
        "x^y": "^", 
        "exp": "e"
    }

    let $textarea = $('#result');
    $textarea.scrollTop($textarea[0].scrollHeight);

    $(".clear").click(function () {
        let res = $("#result")
        let res_val = res.val() == undefined ? "" : res.val()
        let tmp_arr = res_val.split('\n')
        tmp_arr.pop()
        res_val = tmp_arr.join('\n')
        res.val(res_val)
    });

    $(".bs").click(function () {
        let res = $("#result")
        let res_val = res.val() == undefined ? "" : res.val()
        res_val = check_str(res_val)
        res.val(res_val)
    });

    $(".type").click(function () {
        let res = $("#result")
        let k = dict[$(this).val()]
        let res_val = (res.val() == undefined ? "" : res.val()) + (k == undefined ? "" : k)
        res.val(res_val)
    });

    function check_str(s) {
        let dict_values = Object.values(dict)
        let res_len = s.length
        let res_val = s
        for (let v of dict_values) {
            if (res_val.endsWith(v)) {
                return res_val.slice(0, res_len - v.length)
            }
        };
        return res_val.slice(0, res_len - 1)
    }


    // $('#calc-form').submit(function () {
    //     let expr = $('#result').val().split('\n').pop()
    //     if (expr.indexOf('x') >= 0) {
    //         let result = expr.match(/(^[\s\w\+\-\*\/\^\.\(\)]+)[\s:;]+[xX]\s*=\s*(\d+\.?\d*)$/i)
    //             alert(result[1])
    //     }
    //     $("#result").val(expr);
    //     return true;
    // });
});

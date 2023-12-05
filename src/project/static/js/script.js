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
        let res = $("#result");
        let res_val = res.val() == undefined ? "" : res.val();
        let tmp_arr = res_val.split('\n');
        tmp_arr.pop();
        res_val = tmp_arr.join('\n');
        res.val(res_val);
    });

    $(".bs").click(function () {
        let res = $("#result");
        let res_val = res.val() == undefined ? "" : res.val();
        res_val = check_str(res_val);
        res.val(res_val);
    });

    $(".type").click(function () {
        let res = $("#result");
        let k = dict[$(this).val()];
        let res_val = (res.val() == undefined ? "" : res.val()) + (k == undefined ? "" : k);
        res.val(res_val);
    });

    $(".sign").click(function () {
        let res = $textarea[0];
        res.focus();
        let sel = getInputSelection(res);
        let res_val = res.value;
        let num_val = res_val.slice(sel.start, sel.end);
        if (sel.start > 1) {
            if (res_val.at(sel.start - 2) == '-' && res_val.at(sel.start - 1) == '(' && res_val.at(sel.end) == ')') {
                res_val = res_val.slice(0, sel.start - 2) + num_val + res_val.slice(sel.end, res_val.length + 1);
            }
            else {
                res_val = res_val.slice(0, sel.start) + "(-" + num_val + ")" + res_val.slice(sel.end, res_val.length + 1);
            }
        } else {
            res_val = res_val.slice(0, sel.start) + "-" + num_val + res_val.slice(sel.end, res_val.length + 1);
        }
        $("#result").val(res_val);
    });

    function check_str(s) {
        let dict_values = Object.values(dict);
        let res_len = s.length;
        let res_val = s;
        for (let v of dict_values) {
            if (res_val.endsWith(v)) {
                return res_val.slice(0, res_len - v.length);
            }
        };
        return res_val.slice(0, res_len - 1);
    }

    function getInputSelection(el) {
        var start = 0, end = 0, normalizedValue, range,
            textInputRange, len, endRange;

        if (typeof el.selectionStart == "number" && typeof el.selectionEnd == "number") {
            start = el.selectionStart;
            end = el.selectionEnd;
        } else {
            range = document.selection.createRange();

            if (range && range.parentElement() == el) {
                len = el.value.length;
                normalizedValue = el.value.replace(/\r\n/g, "\n");

                textInputRange = el.createTextRange();
                textInputRange.moveToBookmark(range.getBookmark());

                endRange = el.createTextRange();
                endRange.collapse(false);
                function goToSomeView(){
                    document.location.href = "{% url 'some_view' %}"
                   }
                    start += normalizedValue.slice(0, start).split("\n").length - 1;

                    if (textInputRange.compareEndPoints("EndToEnd", endRange) > -1) {
                        end = len;
                    } else {
                        end = -textInputRange.moveEnd("character", -len);
                        end += normalizedValue.slice(0, end).split("\n").length - 1;
                    }
                }
            }

        return {
            start: start,
            end: end
        };
    }

});

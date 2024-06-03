$(document).ready(function () {
    // Добавление элементов в список
    $('#addButton').click(function () {
        const text = $('#textInput').val();
        if (text.trim() !== '') {
            if ($('input[name="addPosition"]:checked').val() === 'start') {
                $('#item-list').prepend('<li>' + text + '</li>');
            } else {
                $('#item-list').append('<li>' + text + '</li>');
            }
            $('#textInput').val('');
        }
    });

    // Клонирование параграфов
    $('#cloneButton').click(function () {
        $('#paragraph').clone().appendTo('#cloneDiv');
    });

    // Работа со стилями и удаление изображения
    $('#shrinkButton').click(function () {
        $('#image').css({
            width (index, width) {
                return `${+width.replace('px', '') * 0.9}px`
            },
            height: 'auto'
        });
    });

    $('#deleteButton').click(function () {
        $('#image').remove();
    });

    // Анимация
    $('#animateButton').click(function () {
        $('#animateBox').animate({
            width: '200px',
            height: '200px',
            backgroundColor: '#ff0000'
        }, 1000).animate({
            width: '100px',
            height: '100px',
            backgroundColor: '#0000ff'
        }, 1000);
    });

    // Фильтрация таблицы
    $('#filterInput').on('keyup', function () {
        const value = $(this).val().toLowerCase();
        const column = $('#columnSelect').val();
    
        $('#infoTable tbody tr').filter(function () {
            $(this).toggle($(this).find('td').eq(column).text().toLowerCase().indexOf(value) > -1);
        });
    });
});
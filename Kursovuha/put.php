<?php
if ($_SERVER['REQUEST_METHOD'] === 'PUT') {
    // Получение тела PUT запроса
    $body = file_get_contents('php://input');
    
    // Вывод полученного тела запроса
    echo "Received PUT data: " . $body;
    
}  elseif ($_SERVER['REQUEST_METHOD'] === 'DELETE') {
    // Обработка DELETE запроса
    echo "This is a DELETE request\n";
    
    // Добавьте код для выполнения удаления файла, например:
    $fileToDelete = '/srv/http/mywebsite/test.json';
    
    if (file_exists($fileToDelete)) {
        if (unlink($fileToDelete)) {
            echo "File deleted successfully\n";
        } else {
            echo "Failed to delete the file\n";
        }
    } else {
        echo "File does not exist\n";
    }
    
} elseif ($_SERVER['REQUEST_METHOD'] === 'GET') {
    // Получение содержимого файла текущего скрипта
    $scriptContent = file_get_contents(__FILE__);
    
    // Вывод содержимого файла
    echo "Content of this script file:\n\n";
    echo $scriptContent;
    
} elseif ($_SERVER['REQUEST_METHOD'] === 'HEAD') {
    // Отправка HEAD запроса и получение заголовков ответа
    $headers = get_headers(__FILE__);
    
    // Вывод заголовков ответа
    echo "Headers:\n\n";
    foreach ($headers as $header) {
        echo $header . "\n";
    }
    
} elseif ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
    // Установка заголовков ответа для поддержки OPTIONS
    header('Access-Control-Allow-Methods: OPTIONS, GET, POST, PUT, DELETE');
    header('Allow: OPTIONS, GET, POST, PUT, DELETE');
    
} elseif ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Получение тела POST запроса
    $body = file_get_contents('php://input');
    
    // Вывод полученного тела запроса
    echo "Received POST data: " . $body;
    
} else {
    // Обработка других методов
    echo "Unsupported request method";
}
?>

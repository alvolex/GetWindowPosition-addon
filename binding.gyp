{
    "targets": [
        {
            "target_name": "GetWindowPosition",
            "sources": ["GetWindowPosition.cc"],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            "defines": [
                "NAPI_CPP_EXCEPTIONS"
            ]
        }
    ]
}
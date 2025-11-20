package com.estacionamento.api;

import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/vagas")
@CrossOrigin("*")
public class VagaController {

    private final VagaService vagaService;

    public VagaController(VagaService vagaService) {
        this.vagaService = vagaService;
    }

    @GetMapping
    public List<Vaga> listarTodas() {
        return vagaService.listarTodas();
    }

    @GetMapping("/{id}")
    public Vaga buscarPorId(@PathVariable Long id) {
        return vagaService.buscarPorId(id);
    }

    @PostMapping
    public Vaga criar(@RequestBody Vaga vaga) {
        return vagaService.salvar(vaga);
    }

    @PutMapping("/{id}/ocupar")
    public Vaga ocupar(@PathVariable Long id) {
        return vagaService.ocupar(id);
    }

    @PutMapping("/{id}/liberar")
    public Vaga liberar(@PathVariable Long id) {
        return vagaService.liberar(id);
    }
}
